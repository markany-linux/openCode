#include "config_handler.h"

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "dprint.h"
#include "string_parser.h"
#include "file_handler.h"


/// 리스트 관리 전역 변수
LIST_HEAD( config_list_head );

/// 리스트 동기화 제어를 위한 동기화 변수
pthread_mutex_t g_config_lock = PTHREAD_MUTEX_INITIALIZER;


/**
 * @brief   설정 라벨과 값을 리스트에 추가
 * 
 * @param   label__ 추가할 설정 라벨
 * @param   value__ 추가할 설정 값
 * 
 * @return  리스트 추가 성공 true, 실패 false
 */
static mild_bool add_config_list(
    mild_str                    label__,
    mild_str                    value__
    )
{
    PAGENT_CONFIG config = mild_null;

    NULL_PTR_RETURNS( label__, value__ );

    /// 1. 리스트에 보관할 구조체 할당
    config = ( PAGENT_CONFIG )malloc( sizeof( AGENT_CONFIG ) );
    NULL_PTR_RETURN( config );

    /// 2. 할당된 메모리 초기화
    memset( config, 0x00, sizeof( AGENT_CONFIG ) );

    /// 3. 전달된 라벨과 값을 복사
    memcpy( config->label, label__, strlen( label__ ) );
    memcpy( config->value, value__, strlen( value__ ) );

    /// 4. 리스트에 추가
    pthread_mutex_lock( &g_config_lock );
    list_add_tail( &config->ptr, &config_list_head );
    pthread_mutex_unlock( &g_config_lock );

    return mild_true;
}


/**
 * @brief   설정 파일을 개방하여 디스크립터를 반환
 * 
 * @param   fd__        반환할 디스크립터
 * @param   pathname__  개방할 설정 파일 경로
 * 
 * @return  개방 성공 true, 실패 false
 */
static mild_bool open_config_file(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    )
{
    mild_i32 fd = 0;

    /// 1. 파일 개방
    fd = open( pathname__, O_RDONLY );
    NULL_PTR_RETURN( fd );

    /// 2. 반환 디스크립터에 할당
    *fd__ = fd;

    return mild_true;
}


/**
 * @brief   설정 라벨에 해당하는 문자 여부 반환
 *          설정 라벨은 숫자, 알파벳 대문자, -, _, '.'만 허용
 * 
 * @param   char__  확인할 문자
 * 
 * @return  설정 라벨 허용 문자라면 true, 아니면 false
 */
static mild_bool check_config_char(
    mild_i8                     char__
    )
{
    /// 1. 0 ~ 9 사이의 숫자 여부 확인
    if( ( '0' <= char__ ) && ( '9' >= char__ ) )
        return mild_true;

    /// 2. A ~ Z 사이의 문자 여부 확인
    if( ( 'A' <= char__ ) && ( 'Z' >= char__ ) )
        return mild_true;

    /// 3. -, _, . 문자 여부 확인
    if( ( '-' == char__ ) || ( '_' == char__ ) || ( '.' == char__ ) )
        return mild_true;

    return mild_false;
}


/**
 * @brief   설정 값에 해당하는 문자 여부 반환
 *          check_config_char( ) 확인에 소문자 a ~ z 추가 확인
 * 
 * @param   char__  확인할 문자
 * @param   space__ 공백 허용 여부
 * 
 * @return  설정 값 허용 문자라면 true, 아니면 false
 */
static mild_bool check_value_char(
    mild_i8                     char__,
    mild_bool                   space__
    )
{
    /// 1. 소문자를 제외한 문자 여부 확인
    if( mild_false != check_config_char( char__ ) )
        return mild_true;

    /// 2. 소문자 a ~ z 문자 여부 확인
    if( ( 'a' <= char__ ) && ( 'z' >= char__ ) )
        return mild_true;

    /// 3. 경로 포함 '/' 문자 확인
    if( '/' == char__ )
        return mild_true;

    /// 4. 설정 값의 공백을 허용할 것인지 여부
    if( mild_false != space__ )
    {
        if( ' ' == char__ )
            return mild_true;
    }

    return mild_false;
}


/**
 * @brief   설정 라벨 획득 및 변위 값 반환
 * 
 * @param   buf__   설정 라벨을 획득할 버퍼
 * @param   label__ 획득한 라벨을 저장할 버퍼
 * 
 * @return  설정 라벨의 길이
 */
static mild_i32 get_config_label(
    mild_str                    buf__,
    mild_str                    label__
    )
{
    mild_i32 i = 0;

    /// 1. 설정 라벨이 아닐 때까지 반복
    while( mild_false != check_config_char( *( buf__ + i ) ) )
    {
        /// 1-1. 반환 라벨에 현재 문자를 복사
        *( label__ + i ) = *( buf__ + i );
        /// 1-2. 변위 증가
        i++;
    }

    /// 2. 변위 값 반환
    return i;
}


/**
 * @brief   설정 값 획득 및 변위 값 반환
 * 
 * @param   buf__   설정 값을 획득할 버퍼
 * @param   value__ 획득 값을 저장할 버퍼
 * 
 * @return  설정 값의 길이
 */
static mild_i32 get_config_value(
    mild_str                    buf__,
    mild_str                    value__
    )
{
    mild_i32 i = 0;

    /// 1. 설정 값이 아닐 때까지 반복
    while( mild_false != check_value_char( *( buf__ + i ), mild_true ) )
    {
        /// 1-1. 반환 값에 현재 문자를 복사
        *( value__ + i ) = *( buf__ + i );
        /// 1-2. 변위 증가
        i++;
    }

    /// 2. 변위 값 반환
    return i;
}


/**
 * @brief   설정 라벨에서 설정 값 사이의 문자 개수를 반환
 * 
 * @param   buf__   확인할 버퍼
 * 
 * @return  버퍼 시작부터 설정 값이 처음 나타나는 위치의 문자 개수
 */
static mild_i32 skip_to_value(
    mild_str                    buf__
    )
{
    mild_i32 i = 0;

    /// 1. 설정 값에 해당하는 문자가 확인될 때까지 반복
    while( mild_false == check_value_char( *( buf__ + i ) , mild_false ) )
    {
        /// 1-1. 개수 증가
        i++;
    }

    /// 2. 개수 반환
    return i; 
}


/**
 * @brief   설정 라벨이 존재하는 위치까지의 변위를 반환
 * 
 * @param   buf__   확인 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  설정 라벨까지의 변위
 */
static mild_i32 move_to_config(
    mild_str                    buf__,
    mild_i32                    len__
    )
{
    mild_i32 cnt = 0;
    mild_i32 moved = 0;
    mild_str ptr = buf__;

    /// 1. 설정 라벨을 만날 때까지 반복
    while( mild_true )
    {
        /// 1-1. 현재 위치 또는 다음 라인 첫 문자의 주석('#') 여부 확인
        if( '#' == *ptr )
        {
            /// 1-1-1T. 주석 라인을 건너 뛰기 위한 변위 값 획득
            moved = get_next_line_offset( ptr, len__ );
            /// 1-1-2T. 변위 값을 더해 다음 위치로 포인터 이동
            ptr = ( ptr + moved );
            /// 1-1-3T. 변위 값을 누적
            cnt += moved;
            /// 1-1-4T. 비교를 위해 반복문의 시작으로 이동
            continue;
        }

        /// 1-2. 문자가 설정 값에 해당하는 문자면 반복을 빠져나감
        if( mild_false != check_config_char( *ptr ) )
            break;

        /// 1-3. 다음 위치로 포인터 이동 및 변위 값 누적
        /// 설정 값 시작 문자가 아니고, '\n', ' ', '\t'와 같은 문자면 다음으로 이동
        ptr++;
        cnt++;
    }

    /// 2. 누적된 변위 값을 반환
    return cnt;
}


/**
 * @brief   설정 값을 읽어 들이기 위한 준비 작업 수행
 * 
 * @param   pathname__  설정 파일의 경로
 * @param   fd__        설정 파일 개방 파일 디스크립터 반환
 * @param   size__      설정 파일의 크기
 * @param   buf__       읽어 들인 설정 파일 버퍼
 * 
 * @return  설정 파일 접근 성공 true, 실패 false
 */
static mild_bool prepare_config_search(
    mild_cstr                   pathname__,
    mild_i32                    *fd__,
    mild_i32                    *size__,
    mild_str                    *buf__
    )
{
    /// 1. 설정 파일의 크기를 획득. 존재 확인은 내부에서 수행
    if( mild_false == get_file_size( pathname__, size__ ) )
    {
        dprint( _CM_, "Cannot get config file[ %s ] size", pathname__ );
        return mild_false;
    }

    /// 2. 설정 파일을 개방
    if( mild_false == open_config_file( fd__, pathname__ ) )
    {
        dprint( _CM_, "Cannot open config file[ %s ]", pathname__ );
        return mild_false;
    }

    /// 3. 설정 파일 크기만큼 버퍼 획득
    *buf__ = ( mild_str )malloc( *size__ );
    if( mild_null == *buf__ )
    {
        /// 3-1F. 버퍼 획득 실패 시, 디스크립터를 닫고 반환
        close( *fd__ );

        dprint( _CM_, "Cannot allocate memory for config file read" );
        return mild_false;
    }

    /// 4. 설정 파일 읽기
    if( 0 > read( *fd__, *buf__, *size__ ) )
    {
        /// 4-1F. 파일 디스크립터를 닫음
        close( *fd__ );
        /// 4-2F. 할당된 버퍼를 해제
        free( *buf__ );

        dprint( _CM_, "Cannot read config file[ %s ]", pathname__ );
        return mild_false;
    }

    return mild_true;
}


void disp_config_list( void )
{
    mild_i32 i = 0;
    PAGENT_CONFIG config = mild_null;
    struct list_head *pos = mild_null;

    pthread_mutex_lock( &g_config_lock );

    list_for_each( pos, &config_list_head )
    {
        config = list_entry( pos, AGENT_CONFIG, ptr );

        dprint( _IM_, "%d: config[ %s ] value[ %s ]\n", ++i, config->label, config->value );
    }

    pthread_mutex_unlock( &g_config_lock );
}


void dispConfigListValue( void )
{
    return disp_config_list( );
}


mild_bool init_config_list(
    mild_cstr                   pathname__
    )
{
    mild_i32 fd = 0;
    mild_i32 offset = 0;
    mild_i32 moved = 0;
    mild_i32 size = 0;
    mild_i8 label[ STRLEN_32 ] = { 0, };
    mild_i8 value[ STRLEN_64 ] = { 0, };
    mild_str ptr = mild_null;
    mild_str buf = mild_null;

    NULL_PTR_RETURN( pathname__ );

    /// 1. 설정 정보 획득을 위한 준비
    if( mild_false == prepare_config_search( pathname__, &fd, &size, &buf ) )
        return mild_false;

    ptr = buf;

    /// 2. 설정 정보 획득 완료까지 반복
    while( mild_true )
    {
        /// 2-1. 현재 위치에서 설정 라벨 위치까지의 변위 획득
        offset = move_to_config( ptr, ( size - moved ) );
        /// 2-2. 라벨까지 포인터 이동 및 변위 누적
        ptr = ( ptr + offset );
        moved += offset;

        /// 2-3. 읽어들인 버퍼를 모두 확인하였으면 반복 종료
        if( size <= moved )
            break;

        /// 2-4. 설정 라벨의 변위 및 라벨 획득
        offset = get_config_label( ptr, label );
        /// 2-5. 포인터 이동 및 변위 누적
        ptr = ( ptr + offset );
        moved += offset;

        /// 2-6. 설정 라벨 이후, 설정 값까지의 변위 획득
        offset = skip_to_value( ptr );
        /// 2-7. 설정 값까지 포인터 이동 및 변위 누적
        ptr = ( ptr + offset );
        moved += offset;

        /// 2-8. 설정 값의 변위 및 값 획득
        offset = get_config_value( ptr, value );
        /// 2-9. 설정 값 다음 위치로 포인터 이동 및 변위 누적
        ptr = ( ptr + offset );
        moved += offset;

        /// 2-10. 획득된 설정 라벨과 값을 리스트에 등록
        add_config_list( label, value );

        /// 2-11. 획득 버퍼 초기화
        memset( label, 0x00, STRLEN_32 );
        memset( value, 0x00, STRLEN_64 );
    }

    /// 3. 파일을 닫고, 버퍼 메모리 해제
    close( fd );
    free( buf );

    return mild_true;
}


mild_bool initConfigList(
    mild_cstr                   pathname__
    )
{
    return init_config_list( pathname__ );
}


mild_bool get_config_list_value(
    mild_cstr                   label__,
    mild_str                    value__,
    mild_u32                    len__
    )
{
    PAGENT_CONFIG config = mild_null;
    struct list_head *pos = mild_null;

    NULL_PTR_RETURNS( label__, value__ );

    /// 1. 리스트 접근을 위한 잠금
    pthread_mutex_lock( &g_config_lock );

    /// 2. 리스트 노드들 순환
    list_for_each( pos, &config_list_head )
    {
        /// 2-1. 리스트의 현재 노드 포인터 획득
        config = list_entry( pos, AGENT_CONFIG, ptr );

        /// 2-2. 요청 라벨과 동일한 라벨인지 확인
        if( 0 == strncmp( label__, config->label, strlen( label__ ) ) )
        {
            /// 설정 값을 반환할 버퍼 길이 확인
            if( len__ <= strlen( config->value ) )
            {
                dprint( _CM_, "Request buffer size isnot enough" );
                pthread_mutex_unlock( &g_config_lock );
                return mild_false;
            }
            /// 2-2-1T. 반환 버퍼에 설정 값을 복사
            memcpy( value__, config->value, strlen( config->value ) );
            /// 2-2-2T. 리스트 잠금 해제
            pthread_mutex_unlock( &g_config_lock );
            return mild_true;
        }
    }

    /// 3. 리스트 잠금 해제
    pthread_mutex_unlock( &g_config_lock );

    return mild_false;
}


mild_bool getConfigListValue(
    mild_cstr                   label__,
    mild_str                    value__,
    mild_u32                    len__
    )
{
    return get_config_list_value( label__, value__, len__ );
}


void cleanup_config_list( void )
{
    PAGENT_CONFIG config = mild_null;

    /// 1. 정리할 리스트가 존재하는지 여부 확인
    if( 0 != list_empty( &config_list_head ) )
        return;

    /// 2. 리스트 접근을 위한 잠금
    pthread_mutex_lock( &g_config_lock );

    /// 3. 리스트가 존재하지 않을 때까지 반복
    while( 0 == list_empty( &config_list_head ) )
    {
        /// 3-1. 리스트의 현재 노드 포인터 획득
        config = list_entry( config_list_head.next, AGENT_CONFIG, ptr );
        /// 3-2. 리스트에서 현재 노드 제거
        list_del( &config->ptr );
        /// 3-3. 메모리 초기화
        memset( config, 0x00, sizeof( AGENT_CONFIG ) );
        /// 3-4. 동적 메모리 해제
        free( config );
    }

    /// 4. 리스트 잠금 해제
    pthread_mutex_unlock( &g_config_lock );

    dprint( _IM_, "All configuration info. cleanup" );
}


void cleanupConfigList( void )
{
    return cleanup_config_list( );
}