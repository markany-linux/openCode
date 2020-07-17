/**
 * \file    opencode_sysfs.h
 * 
 * \brief   
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __OPENCODE_SYSFS_H__
#define __OPENCODE_SYSFS_H__


#include "common.h"


/**
 * @brief   sysfs를 통해 획득할 커널 모듈 정보 구조체
 */
typedef struct sysfs_info_information_for_kernel_object_connect
{
    /// netlink build version
    mild_u32                    vsersion;

    /// netlink state
    mild_bool                   netlink_online;

    /// netlink connection port
    mild_i32                    netlink_port;

} OPENCODE_SYSFS_INFO, *POPENCODE_SYSFS_INFO;


#endif  // #ifndef __OPENCODE_SYSFS_H__
