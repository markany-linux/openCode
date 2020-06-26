#include "system_info.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>

#include <errno.h>

#include "proc_handler.h"
#include "string_parser.h"


/// 커널 정보 파일명 선언
#define KERNEL_VERSION_FILE     "/proc/version"
/// 네트워크 인터페이스 정보 파일명 선언
#define NETWORK_INTERFACE_FILE  "/proc/net/route"

/// 배포판 정보 파일명 및 속성 정보 선언
#define DISTRIB_INFO_FILE       "/etc/os-release"
#define DISTRIB_NAME            "NAME"
#define DISTRIB_PRETTY_NAME     "PRETTY_"DISTRIB_NAME
#define DISTRIB_ID              "ID"
#define DISTRIB_ID_LIKE         DISTRIB_ID"_LIKE"
#define DISTRIB_VERSION         "VERSION"
#define DISTRIB_VERSION_ID      DISTRIB_VERSION"_"DISTRIB_ID


/**
 * @brief   /proc/version에서 커널 버전 정보를 획득하여 반환
 *          표준 커널을 사용하는 배포판들은 동일한 형태의 문자열로 구성
 *          파일은 "Linux version"으로 시작하고, 바로 뒤이어 커널 버전을 문자열로 제공
 *          즉, 2번째 공백 이후에 다음 공백까지가 커널 버전을 획득하여 반환
 *          ! 무조건 14번째 위치부터 획득하는 방법도 있으나 좋지 않은 방법
 * 
 * @param   buffer__    /proc/version 파일을 읽어들인 버퍼
 * @param   version__   버퍼에서 추출한 커널 버전 정보
 */
static void parsing_kernel_version(
    mild_str                    buffer__,
    mild_str                    version__
    )
{
    mild_i32 cnt = 0;

    /// "Linux"까지의 문자 개수는 5개. 공백 다음 위치로 포인터 이동을 위해 1을 더함
    cnt = get_space_pos( buffer__ ) + 1;
    /// "version"까지의 문자 개수를 획득하고 공백 다음 위치 이동을 위해 1을 더함
    cnt += get_space_pos( buffer__ + cnt ) + 1;

    /// 2번째 공백 이후의 문자열을 다음 공백 문자 이전까지 버퍼에 복사
    memcpy( version__, buffer__ + cnt, get_space_pos( buffer__ + cnt ) );
}


/**
 * @brief   커널 버전 번호만을 획득하여 반환
 * 
 * @param   version__   현재 커널 버전 정보를 갖는 버퍼
 */
static void get_plain_kernel_version(
    mild_str                    version__
    )
{
    mild_i32 i = 0;
    mild_i32 cnt = 0;
    mild_i8 tmp[ STRLEN_16 ] = { 0, };
    mild_str ptr = version__;

    /// minor 버전 위치인 2개의 '.'까지 임시 버퍼에 기록
    for( ; i < strlen( version__ ); i++ )
    {
        /// 먼저 임시 버퍼에 현재 문자를 복사
        tmp[ i ] = *( ptr + i );

        /// 복사한 문자가 '.'이면 카운트 증가
        if( '.' == *( ptr + i ) )
            cnt++;

        /// '.' 개수가 2개이면 현재 위치가 minor 번호 뒤의 '.' 위치이므로 반복 종료
        if( 2 == cnt )
            break;
    }

    /// 전달된 커널 버전 자체가 별도의 추가 정보가 없을 수 있어 현재 위치까지의 값을 백업
    /// 현재 위치인 '.'은 이미 복사가 이루어졌으므로 다음 위치로 i 값을 이동
    cnt = i++;

    /// 남은 길이만큼 반복문에서 문자를 복사
    for( ; i < strlen( version__ ) - cnt; i++ )
    {
        /// 숫자가 아닌 값이 나타나면 반복문을 종료
        if( ( '0' > *( ptr + i ) ) || ( '9' < *( ptr + i ) ) )
            break;

        /// 숫자 값이면 임시 버퍼에 복사
        tmp[ i ] = *( version__ + i );
    }

    /// 원본 문자열을 초기화하고, 추출한 커널 버전 정보를 원본에 복사
    memset( version__, 0x00, STRLEN_32 );
    memcpy( version__, tmp, strlen( tmp ) );
}


/**
 * @brief   "/proc/version" 파일에서 커널 버전을 획득하여 반환하는 메인 함수
 * 
 * @param   version__   획득된 버전을 반환할 버퍼
 * 
 * @return  커널 버전 획득 성공 true, 실패 false
 */
static mild_bool get_kernel_version(
    mild_str                    version__
    )
{
    mild_i32 fd = 0;
    mild_i8 buffer[ STRLEN_512 ] = { 0, };

    /// "/proc/version" 파일을 개방
    fd = open( KERNEL_VERSION_FILE, O_RDONLY );
    if( 0 > fd )
        return mild_false;

    /// 파일 내용을 읽어들임
    if( 0 > read( fd, buffer, STRLEN_512 ) )
    {
        close( fd );
        return mild_false;
    }

    /// 읽어 들인 파일은 더 이상 필요하지 않으므로 닫음
    close( fd );

    /// 버퍼를 파싱하여 커널 버전에 관련된 문자열만 추출
    parsing_kernel_version( buffer, version__ );
    /// 추출된 버퍼에서 순수 커널 버전만 추출
    /// 읽은 커널 버전 정보가 "4.15.0-33-generic"과 같은 경우 "4.15.0"만을 추출
    get_plain_kernel_version( version__ );

    return mild_true;
}


/**
 * @brief   "/proc/net/route" 파일에서 시스템이 사용중인 메인 네트워크 카드의 이름을 획득
 * 
 * @param   nic__   획득한 NIC 이름을 반환할 버퍼
 * 
 * @return  NIC 이름 획득 성공 true, 실패 false
 */
static mild_bool get_default_nic(
    mild_str                    nic__
    )
{
    FILE *file;
    mild_i8 buffer[ STRLEN_128 ] = { 0, };
    mild_str ptr = mild_null;
    mild_str tok = mild_null;

    /// "/proc/net/route" 파일을 개방
    file = fopen( NETWORK_INTERFACE_FILE, "r" );
    if( mild_null == file )
        return mild_false;

    /// 파일 내용을 읽어 들여 메인 NIC 포인터를 획득
    while( fgets( buffer, STRLEN_128, file ) )
    {
        /// NIC 정보 획득을 위해 버퍼를 토큰으로 분리
        ptr = strtok( buffer, " \t" );
        tok = strtok( mild_null, " \t" );

        /// 토큰에 의한 분리가 정상적으로 이루어 졌는지 확인
        if( ( mild_null != ptr ) && ( mild_null != tok ) )
        {
            /// 현재 토큰이 메인 인터페이스 카드인지 여부 확인
            /// 메인 NIC는 Destination 값이 "00000000"으로 설정됨
            if( 0 == strncmp( tok, "00000000", strlen( tok ) ) )
                break;
        }
    }

    /// 파일을 닫음
    fclose( file );

    /// 획득된 메인 NIC 이름을 반환 버퍼에 복사
    memcpy( nic__, ptr, strlen( ptr ) );

    return mild_true;
}


/**
 * @brief   전달된 NIC의 IPv4 주소를 획득하여 반환
 * 
 * @param   nic__   IP 주소를 획득하려는 NIC 이름
 * @param   ip__    IP 주소를 반환할 버퍼
 * 
 * @return  IP 주소 획득 성공 true, 실패 false
 */
static mild_bool get_default_ip(
    mild_str                    nic__,
    mild_str                    ip__
    )
{
    mild_i32 family = 0;
    mild_bool res = mild_false;
    mild_i8 ip[ STRLEN_1024 ] = { 0, };
    struct ifaddrs *ifaddr, *ifa;

    /// NIC 들의 전체 목록을 획득
    if( -1 == getifaddrs( &ifaddr ) )
    {
        printf( "getifaddr fail\n" );
        return mild_false;
    }

    /// 목록에서 대상 NIC의 IPv4 주소를 획득하는 반복문
    for( ifa = ifaddr; mild_null != ifa; ifa = ifa->ifa_next )
    {
        /// 주소를 갖는 인터페이스가 존재하는지 여부 확인
        if( mild_null == ifa->ifa_addr )
            continue;

        /// 주소 체계에서 통신 도메인 값을 획득
        family = ifa->ifa_addr->sa_family;

        /// 현재 NIC가 대상 NIC인지 여부 확인
        if( 0 == strncmp( nic__, ifa->ifa_name, strlen( nic__ ) ) )
        {
            /// TODO: check only IPv4. if check IPv4 use AF_INET6
            /// 통신 도메인이 IPv4 버전인지 확인
            if( AF_INET != family )
                continue;

            /// IP 주소를 획득
            if( 0 != getnameinfo( ifa->ifa_addr, sizeof( struct sockaddr_in ), ip, STRLEN_1024, mild_null, 0, 1 ) )
            {
                printf( "getnameinfo fail\n" );
                break;
            }

            res = mild_true;
            break;
        }
    }

    /// 개방된 인터페이스 목록을 닫음
    freeifaddrs( ifaddr );
    /// 반환 버퍼에 획득한 IP 주소를 복사
    memcpy( ip__, ip, strlen( ip ) );

    return res;
}


/**
 * @brief   로컬 시스템의 호스트 이름과 메인 NIC 그리고 IP 주소를 획득하고 반환하는 메인 함수
 * 
 * @param   system__    획득된 정보를 반환할 구조체
 * 
 * @return  모든 정보 획득 성공 true, 실패 false
 */
static mild_bool get_local_network_info(
    PMADRM_LOCAL_SYSTEM         system__
    )
{
    /// 호스트 이름을 획득
    if( 0 != gethostname( system__->local_hostname, STRLEN_64 ) )
    {
        printf( "fail to gethostname\n" );
        return mild_false;
    }

    /// 메인 NIC 이름을 획득
    if( mild_false == get_default_nic( system__->local_nic ) )
    {
        printf( "fail to get default nic name\n" );
        return mild_false;
    }

    /// IP 주소를 IPv4 버전으로 획득
    /// FIXME: 네트워크가 연결되지 않은 상태에서는 IP 주소 획득이 실패할 수 있음!!!!
    if( mild_false == get_default_ip( system__->local_nic, system__->local_ip ) )
    {
        printf( "fail to get default ip address\n" );
        return mild_false;
    }

    return mild_true;
}


/**
 * @brief   배포판의 정보를 획득하고 반환하는 함수
 *          배포판 라벨과 해당 값 모두 획득하여 반환이 가능
 *          Ex. dis_label=value 형태로 구성. 간단히 다음 구분자 위치까지 복사하여 반환
 * 
 * @param   ptr__   배포판 정보 획득 위치
 * @param   value__ 획득 정보 반환 버퍼
 * @param   sep__   구분자
 * 
 * @return  획득하여 반환한 정보의 길이
 */
static mild_i32 get_distrib_field(
    mild_str                    ptr__,
    mild_str                    value__,
    mild_i8                     sep__
    )
{
    mild_i32 cnt = 0;

    /// 요청 구분자까지의 문자 개수를 카운트
    while( sep__ != *( ptr__ + cnt ) )
    {
        cnt++;
    }

    /// 반환 버퍼에 구분자까지의 값을 복사
    memcpy( value__, ptr__, cnt );

    /// 정보의 길이 반환
    return cnt;
}


/**
 * @brief   배포판의 라벨, 값 쌍을 구분하여 지정 위치에 복사하는 함수
 *          라벨이 보관할 내용이 아니라면 처리하지 않음
 * 
 * @param   system__    획득된 배포판 정보를 기록할 구조체
 * @param   field__     배포판의 라벨
 * @param   value__     라벨에 해당하는 값
 */
static void set_distrib_value(
    PMADRM_LOCAL_SYSTEM         system__,
    mild_str                    field__,
    mild_str                    value__
    )
{
    /// Distribution NAME
    if( 0 == strncmp( DISTRIB_NAME, field__, strlen( DISTRIB_NAME ) ) )
    {
        memcpy( system__->distrib_name, value__, strlen( value__ ) );
    }
    /// Distribution PRETTY_NAME
    else if( 0 == strncmp( DISTRIB_PRETTY_NAME, field__, strlen( DISTRIB_PRETTY_NAME ) ) )
    {
        memcpy( system__->distrib_pretty, value__, strlen( value__ ) );
    }
    /// Distribution ID_LIKE
    else if( 0 == strncmp( DISTRIB_ID_LIKE, field__, strlen( DISTRIB_ID_LIKE ) ) )
    {
        memcpy( system__->distrib_id_like, value__, strlen( value__ ) );
    }
    /// Distribution ID. ID를 ID_LIKE 보다 먼저 처리하면 길이에 의한 문제 발생
    /// ID_LIKE는 ID를 포함하고 있기 때문에 ID에 ID_LIKE 값이 복사되고 ID_LIKE 값을 획득하지 못함
    else if( 0 == strncmp( DISTRIB_ID, field__, strlen( DISTRIB_ID ) ) )
    {
        memcpy( system__->distrib_id, value__, strlen( value__ ) );
    }
    /// Distribution VERSION_ID
    else if( 0 == strncmp( DISTRIB_VERSION_ID, field__, strlen( DISTRIB_VERSION_ID ) ) )
    {
        memcpy( system__->distrib_version_id, value__, strlen( DISTRIB_VERSION_ID ) );
    }
    /// Distribution VERSION. 4와 같은 이유로 VERSION_ID 아래에서 처리
    else if( 0 == strncmp( DISTRIB_VERSION, field__, strlen( DISTRIB_VERSION ) ) )
    {
        memcpy( system__->distrib_version, value__, strlen( value__ ) );
    }
}


/**
 * @brief   배포판 정보가 ""으로 묶여 있는 경우 이를 제거하는 함수
 * 
 * @param   str__   배포판 정보 버퍼
 * @param   len__   배포판 정보 버퍼의 총 길이
 */
static void clear_double_quotation(
    mild_str                    str__,
    mild_i32                    len__
    )
{
    mild_i32 len = 0;
    mild_i8 tmp[ STRLEN_64 ] = { 0, };

    /// 정보의 첫 번째 "으로 시작하는지 확인
    if( '\"' != *str__ )
        return;

    /// 정보의 전체 길이 획득
    len = strlen( str__ );
    /// 임시 버퍼에 "" 사이의 값을 복사
    memcpy( tmp, str__ + 1, len - 2 );
    /// 원본 문자열을 초기화
    memset( str__, 0x00, len__ );
    /// 획득한 "" 없는 값을 복사
    memcpy( str__, tmp, strlen( tmp ) );
}


/**
 * @brief   배포판 정보를 획득하는 메인 함수
 * 
 * @param   system__    획득된 정보를 저장할 구조체
 * 
 * @return  정보 획득 성공 true, 실패 false
 */
static mild_bool get_distrib_info(
    PMADRM_LOCAL_SYSTEM         system__
    )
{
    mild_i32 fd = 0;
    mild_i32 cnt = 0;
    mild_i32 moved = 0;
    mild_i8 buffer[ STRLEN_512 ] = { 0, };
    mild_str ptr = buffer;
    mild_i8 field[ STRLEN_64 ] = { 0, };
    mild_i8 value[ STRLEN_128 ] = { 0, };

    /// "/etc/os-release" 파일 개방
    fd = open( DISTRIB_INFO_FILE, O_RDONLY );
    if( 0 > fd )
        return mild_false;

    /// 파일 내용을 읽어 들임
    if( 0 > read( fd, buffer, STRLEN_512 ) )
    {
        printf( "%s read fail\n", DISTRIB_INFO_FILE );
        close( fd );
        return mild_false;
    }

    /// 파일을 닫음
    close( fd );

    /// 파일 내용에서 정보를 추출하는 반복문 수행
    while( strlen( buffer ) > cnt )
    {
        /// 정보 획득 버퍼 초기화
        memset( field, 0x00, STRLEN_64 );
        memset( value, 0x00, STRLEN_128 );

        /// 필드 문자열을 획득
        moved = get_distrib_field( ptr, field, '=' );
        /// 구분자인 '=' 다음으로 포인터와 처리한 문자 개수 증가
        ptr += moved + 1;
        cnt += moved + 1;

        /// 필드 값을 획득
        moved = get_distrib_field( ptr, value, '\n' );
        /// 구분자인 '\n' 다음으로 포인터와 처리한 문자 개수 증가
        ptr += moved + 1;
        cnt += moved + 1;

        /// 값에 존재할 수 있는 "" 제거
        clear_double_quotation( value, sizeof( value ) );

        /// 반환할 구조체에 획득한 정보를 기록
        /// 보관할 필드가 존재하는 경우에만 처리
        set_distrib_value( system__, field, value );
    }

    return mild_true;
}


mild_bool get_system_info(
    PMADRM_LOCAL_SYSTEM         system__
    )
{
    /// 커널 버전 획득
    if( mild_false == get_kernel_version( system__->kernel_version ) )
    {
        return mild_false;
    }

    /// 호스트 이름과 NIC 및 IP 주소 획득
    if( mild_false == get_local_network_info( system__ ) )
    {
        return mild_false;
    }

    /// 배포판에 대한 정보 획득
    if( mild_false == get_distrib_info( system__ ) )
    {
        return mild_false;
    }

    return mild_true;
}


mild_bool getLocalSystemInfo(
    PMADRM_LOCAL_SYSTEM         system__
    )
{
    return get_system_info( system__ );
}
