#include "code_helper.h"

#include <fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>


mild_bool malloc_code_agent(
    POPENCODE_AGENT             *agent__
    )
{
    POPENCODE_AGENT agent = mild_null;

    /// 메모리 할당 및 확인
    agent = ( POPENCODE_AGENT )malloc( sizeof( OPENCODE_AGENT ) );
    if( mild_null == agent )
    {
        printf( "openCode memory allocation fail for agent\n" );
        return mild_false;
    }

    /// 획득 메모리 초기화
    memset( agent, 0x00, sizeof( OPENCODE_AGENT ) );

    /// 처리 완료된 메모리를 전역 변수에 할당
    *agent__ = agent;

    return mild_true;
}


void free_code_agent(
    POPENCODE_AGENT             agent__
    )
{
    /// 메모리가 할당되지 않았다면 처리할 필요 없음
    if( mild_null == agent__ )
        return;

    /// 획득된 정보 초기화
    memset( agent__, 0x00, sizeof( OPENCODE_AGENT ) );

    /// 메모리 해제
    free( agent__ );
}


mild_bool set_user_info(
    mild_i32                    uid__,
    POPENCODE_USER              user__
    )
{
    struct passwd *pwd = mild_null;

    /// 정보 반환 메모리 유효성 여부 확인
    if( mild_null == user__ )
    {
        printf( "NULL pointer received\n" );
        return mild_false;
    }

    /// 사용자의 정보 획득
    pwd = getpwuid( uid__ );

    /// 사용자 아이디, 이름, 홈 디렉터리를 데이터에 기록
    user__->user_id = pwd->pw_uid;
    memcpy( user__->user_name, pwd->pw_name, strlen( pwd->pw_name ) );
    memcpy( user__->user_home, pwd->pw_dir, strlen( pwd->pw_dir ) );

    return mild_true;
}


/**
 * @brief   전달된 경로의 sysfs 파일 존재 여부와 읽기 권한 확인
 * 
 * @param   pathname__  확인할 전체 경로
 * 
 * @return  존재하며 읽기 권한 존재 true, 존재하지 않거나 권한이 없는 경우 false
 */
static mild_bool check_sysfs_file_exist(
    mild_cstr                   pathname__
    )
{
    /// 커널 모듈이 존재하는지 여부를 가장 먼저 확인
    /// 커널 모듈이 존재하지 않으면 sysfs 커널 객체 확인이 의미 없음
    if( mild_false == checkKernelModuleExist( OPENCODE_KERNEL_MODULE ) )
    {
        printf( "Load %s first\n", OPENCODE_KERNEL_MODULE );
        return mild_false;
    }

    /// 요청 경로의 파일이 존재하는지 여부 확인
    if( mild_false == checkFileExist( pathname__ ) )
    {
        printf( "%s load incomplete\n", OPENCODE_KERNEL_MODULE );
        return mild_false;
    }

    /// 요청 경로 파일에 읽기 권한이 존재하는지 여부 확인
    if( mild_false == checkAccessRead( pathname__ ) )
    {
        printf( "Cannot read %s file\n", pathname__ );
        return mild_false;
    }

    return mild_true;
}


mild_bool open_sysfs_get_contents(
    mild_cstr                   file__,
    mild_ptr                    buf__,
    mild_i32                    len__
    )
{
    mild_i32 fd = 0;
    mild_i8 fname[ STRLEN_64 ] = { 0, };

    /// 반환 버퍼 확인
    if( mild_null == buf__ )
    {
        printf( "Received NULL buffer\n" );
        return mild_false;
    }

    /// 획득할 sysfs 파일 경로 생성
    /// Ex) /sys/kernel/openCode/pathname__ 형식으로 생성
    snprintf( fname, STRLEN_64, "%s/%s", SYSFS_TARGET_PATH, file__ );

    /// 요청 파일의 존재와 읽기 권한 존재 여부 확인
    if( mild_false == check_sysfs_file_exist( fname ) )
        return mild_false;

    /// 요청 파일 개방 및 확인 
    fd = open( fname, O_RDONLY );
    if( 0 > fd )
    {
        printf( "Fail to open %s file\n", fname );
        return mild_false;
    }

    /// 요청 길이만큼 읽음
    if( 0 > read( fd, buf__, len__ ) )
    {
        printf( "Fail to read %s file\n", fname );
        close( fd );
        return mild_false;
    }

    /// 디스크립터 해제
    close( fd );

    return mild_true;
}


/// netlink 접근을 위한 정보체 선언
/// 특성 상, 전역 변수로 사용하는 것이 유리
static struct sockaddr_nl g_addr;
static struct sockaddr_nl g_kernel;
struct nlmsghdr *g_msg;
struct iovec g_iov;
struct msghdr g_mhdr;


mild_bool connect_netlink(
    mild_i32                    *fd__
    )
{
    mild_i32 fd = 0;

    /// 커널 모듈 존재 여부 확인
    if( mild_false == checkKernelModuleExist( OPENCODE_KERNEL_MODULE ) )
    {
        printf( "%s not load yet\n", OPENCODE_KERNEL_MODULE );
        return mild_false;
    }

    /// netlink 타입으로 소켓 생성 및 확인
    fd = socket( PF_NETLINK, SOCK_RAW, NETLINK_PORT_NUMBER );
    if( 0 > fd )
    {
        printf( "Fail to connect netlink port\n" );
        return mild_false;
    }

    /// netlink 연결을 위한 소켓 초기화 및 설정
    memset( &g_addr, 0x00, sizeof( g_addr ) );
    g_addr.nl_family = AF_NETLINK;
    g_addr.nl_pid = getpid( );

    /// netlink 바인딩
    if( 0 > bind( fd, ( struct sockaddr* )&g_addr, sizeof( g_addr ) ) )
    {
        printf( "Fail to bind netlink\n" );
        close( fd );
        return mild_false;
    }

    /// 커널 연결 정보 초기화 및 설정
    memset( &g_kernel, 0x00, sizeof( g_kernel ) );
    g_kernel.nl_family = AF_NETLINK;
    g_kernel.nl_pid = 0;
    g_kernel.nl_groups = 0;

    /// 획득된 디스크립터 반환
    *fd__ = fd;

    return mild_true;
}


mild_bool get_netlink_data(
    mild_i32                    fd__,
    PNETLINK_DATA               data__
    )
{
    mild_i32 ret = 0;
    NETLINK_DATA data = { 0, };
    PNETLINK_DATA ptr = mild_null;

    /// netlink 전달 메시지 헤더 생성 및 초기화
    g_msg = ( struct nlmsghdr* )malloc( NLMSG_SPACE( sizeof( NETLINK_DATA ) ) );
    memset( g_msg, 0x00, NLMSG_SPACE( sizeof( NETLINK_DATA ) ) );

    /// 메시지 헤더 설정
    g_msg->nlmsg_len = NLMSG_SPACE( sizeof( NETLINK_DATA ) );
    g_msg->nlmsg_pid = getpid( );
    g_msg->nlmsg_flags = 0;

    /// 전달 데이터 설정. 아무것도 설정하지 않아도 문제 없음
    data.pid = getpid( );

    /// 메시지 헤더에 데이터 복사
    memcpy( NLMSG_DATA( g_msg ), &data, sizeof( NETLINK_DATA ) );

    /// iov 버퍼와 길이 설정
    g_iov.iov_base = ( void* )g_msg;
    g_iov.iov_len = g_msg->nlmsg_len;

    /// 메시지 헤더 정보 설정 및 iov 연결
    g_mhdr.msg_name = ( void* )&g_kernel;
    g_mhdr.msg_namelen = sizeof( g_kernel );
    g_mhdr.msg_iov = &g_iov;
    g_mhdr.msg_iovlen = 1;

    /// netlink로 데이터 전달
    ret = sendmsg( fd__, &g_mhdr, 0 );
    if( 0 > ret )
    {
        printf( "Fail to send\n" );
        free( g_msg );
        return mild_false;
    }

    /// netlink에서 데이터 획득
    ret = recvmsg( fd__, &g_mhdr, 0 );
    if( 0 > ret )
    {
        printf( "Fail to get\n" );
        free( g_msg );
        return mild_false;
    }

    /// 전달받은 데이터 영역 포인터 획득 및 정보 출력
    ptr = NLMSG_DATA( g_msg );

    /// 반환 버퍼에 데이터 복사
    memcpy( data__, ptr, sizeof( NETLINK_DATA ) );

    /// 할당한 메모리 해제
    free( g_msg );

    return mild_true;
}
