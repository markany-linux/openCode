#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include "../common.h"

/// !! user 포팅 완료시 파일을 제거할 것

/// netlink 통신을 위해 필요한 자료 선언
int g_fd;
static struct sockaddr_nl g_addr;
static struct sockaddr_nl g_kernel;
struct nlmsghdr *g_msg;
struct iovec g_iov;
struct msghdr g_mhdr;


mild_bool connect_netlink( void )
{
    /// netlink 타입으로 소켓 생성 및 확인
    g_fd = socket( PF_NETLINK, SOCK_RAW, NETLINK_PORT_NUMBER );
    if( 0 > g_fd )
    {
        printf( "Fail to connect netlink port\n" );
        return -1;
    }

    /// 소켓 초기화 및 설정
    memset( &g_addr, 0x00, sizeof( g_addr ) );
    g_addr.nl_family = AF_NETLINK;
    g_addr.nl_pid = getpid( );

    /// netlink 바인딩
    if( 0 > bind( g_fd, ( struct sockaddr* )&g_addr, sizeof( g_addr ) ) )
    {
        printf( "Fail to bind netlink\n" );
        close( g_fd );
        return -1;
    }

    /// 커널 연결 정보 초기화 및 설정
    memset( &g_kernel, 0x00, sizeof( g_kernel ) );
    g_kernel.nl_family = AF_NETLINK;
    g_kernel.nl_pid = 0;
    g_kernel.nl_groups = 0;

    return mild_true;
}


void get_netlink_data( void )
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
    ret = sendmsg( g_fd, &g_mhdr, 0 );
    if( 0 > ret )
    {
        printf( "Fail to send\n" );
        return;
    }

    /// netlink에서 데이터 획득
    ret = recvmsg( g_fd, &g_mhdr, 0 );
    if( 0 > ret )
    {
        printf( "Fail to get\n" );
        return;
    }

    /// 전달받은 데이터 영역 포인터 획득 및 정보 출력
    ptr = NLMSG_DATA( g_msg );
    printf( "PID[ %d ] UID[ %d ] FNAME[ %s ], TASK[ %s ] REMAIN[ %d ]\n",
        ptr->pid, ptr->uid, ptr->fname, ptr->task, ptr->remain );

    /// 할당한 메모리 해제
    free( g_msg );
}


int main( void )
{
    /// netlink 연결 시도
    if( mild_false == connect_netlink( ) )
    {
        return -1;
    }

    /// 데이터 송/수신
    get_netlink_data( );

    close( g_fd );

    return 0;
}


