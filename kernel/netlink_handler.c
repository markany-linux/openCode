#include "netlink_handler.h"

#include <linux/cred.h>

#include "access_list.h"


struct sock *g_netlink_socket;


static void set_no_log_info(
    PNETLINK_DATA               log__
    )
{
    log__->pid = current->pid;
    memcpy( log__->fname, NETLINK_NO_LOG_MESSAGE, strlen( NETLINK_NO_LOG_MESSAGE ) );
    memcpy( log__->task, current->comm, strlen( current->comm ) );
    log__->remain = mild_false;
}


void netlink_log_handler(
    struct sk_buff              *skb__
    )
{
    mild_i32 pid = 0;
    NETLINK_DATA node = { 0, };
    PNETLINK_DATA ptr = mild_null;
    struct nlmsghdr *msg_hdr = mild_null;
    struct sk_buff *skb_out = mild_null;
    const struct cred *cr = get_current_cred( );

    msg_hdr = ( struct nlmsghdr* )skb__->data;

    ptr = nlmsg_data( msg_hdr );

    pid = msg_hdr->nlmsg_pid;

    skb_out = nlmsg_new( sizeof( NETLINK_DATA ), 0 );
    if( !skb_out )
    {
        printk( "Fail to new sk_buff\n" );
        return;
    }

    msg_hdr = nlmsg_put( skb_out, 0, 0, NLMSG_DONE, sizeof( NETLINK_DATA ), 0 );

    NETLINK_CB( skb_out ).dst_group = 0;

    if( mild_false == checkAccessListRemain( ) )
    {
        set_no_log_info( &node );
    }
    else
    {
        if( mild_false == getAccessList( &ptr ) )
        {
            set_no_log_info( &node );
        }
        else
        {
            memcpy( &node, ptr, sizeof( NETLINK_DATA ) );
        }
    }

    node.uid = ( mild_i32 )cr->uid.val;

    memcpy( nlmsg_data( msg_hdr ), &node, sizeof( NETLINK_DATA ) );

    if( 0 > nlmsg_unicast( g_netlink_socket, skb_out, pid ) )
    {
        printk( "Fail to sending back user\n" );
    }
}
