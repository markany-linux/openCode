/**
 * \file    opencode_sysfs.h
 * 
 * \brief   sysfs 파일에서 획득하는 커널 모듈 접근 정보
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
    /// kernel module version
    mild_u32                    lkm_version;

    /// netlink version
    mild_u32                    netlink_vsersion;

    /// netlink state
    mild_bool                   netlink_online;

    /// netlink connection port
    mild_i32                    netlink_port;

} OPENCODE_SYSFS_INFO, *POPENCODE_SYSFS_INFO;


#endif  // #ifndef __OPENCODE_SYSFS_H__
