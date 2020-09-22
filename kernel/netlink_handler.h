/**
 * \file    netlink_handler.h
 * 
 * \brief   
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __NETLINK_HANDLER_H__
#define __NETLINK_HANDLER_H__


#include "kcommon.h"

#include <net/sock.h>
#include <linux/netlink.h>


extern struct sock *g_netlink_socket;


extern void netlink_log_handler(
    struct sk_buff              *skb__
    );


#endif  // #ifndef __NETLINK_HANDLER_H__
