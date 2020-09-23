/**
 * \file    netlink_init.h
 * 
 * \brief   netlink 커널 객체 생성 및 해제 인터페이스 구현
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __NETLINK_INIT_H__
#define __NETLINK_INIT_H__


#include "kcommon.h"


/**
 * @brief   netlink 커널 객체 생성 및 등록
 * 
 * @return  생성 및 등록 성공 true, 실패 false
 */
extern mild_bool initNetLinkSocket( void );


/**
 * @brief   netlink 커널 객체 해제
 */
extern void exitNetLinkSocket( void );


#endif  // #ifndef __NETLINK_INIT_H__
