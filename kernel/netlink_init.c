#include "netlink_init.h"

#include "netlink_handler.h"


mild_bool initNetLinkSocket( void )
{
    struct netlink_kernel_cfg cfg = { .input = netlink_log_handler, };

    g_netlink_socket = netlink_kernel_create( &init_net, NETLINK_PORT_NUMBER, &cfg );

    if( mild_null == g_netlink_socket )
    {
        sock_release( g_netlink_socket->sk_socket );
        return mild_false;
    }

    return mild_true;
}


void exitNetLinkSocket( void )
{
    sock_release( g_netlink_socket->sk_socket );

    netlink_kernel_release( g_netlink_socket );

    printk( "NetLink cleanup\n" );
}
