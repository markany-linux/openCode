/**
 * \file    opencode_control.h
 * 
 * \brief   
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __OPENCODE_CONTROL_H__
#define __OPENCODE_CONTROL_H__


#include "common.h"

#include <pthread.h>


/**
 * @brief   스레드 핸들 및 상태 정보 구조체
 */
typedef struct opencode_agent_thread_control_info
{
    /// netlink thread id
    pthread_t                   netlink_tid;

    /// sysfs thread id
    pthread_t                   sysfs_tid;

    /// thread start state
    mild_bool                   thread_state;

} OPENCODE_CONTROL, *POPENCODE_CONTROL;


#endif  // #ifndef __OPENCODE_CONTROL_H__
