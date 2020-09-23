/**
 * \file    netlink_handler.h
 * 
 * \brief   사용자 프로그램과 실제 통신 수행 핸들러 구현
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


/// netlink 소켓
extern struct sock *g_netlink_socket;


/**
 * @brief   netlink 소켓 통신 처리기
 * 
 * @param   skb__   전달받은 정보
 */
extern void netlink_log_handler(
    struct sk_buff              *skb__
    );


#endif  // #ifndef __NETLINK_HANDLER_H__
