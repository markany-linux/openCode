#include "netlink_init.h"

#include "netlink_handler.h"


mild_bool initNetLinkSocket( void )
{
    /// netlink_handler에 등록된 처리기를 등록
    struct netlink_kernel_cfg cfg = { .input = netlink_log_handler, };

    /// netlink 커널 객체 생성
    g_netlink_socket = netlink_kernel_create( &init_net, NETLINK_PORT_NUMBER, &cfg );

    /// 커널 객체 생성 여부 확인
    if( mild_null == g_netlink_socket )
    {
        /// 생성된 소켓 해제
        sock_release( g_netlink_socket->sk_socket );
        return mild_false;
    }

    return mild_true;
}


void exitNetLinkSocket( void )
{
    /// 소켓 해제
    sock_release( g_netlink_socket->sk_socket );

    /// netlink 커널 객체 해제
    netlink_kernel_release( g_netlink_socket );

    printk( "NetLink cleanup\n" );
}
