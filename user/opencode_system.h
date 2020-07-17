/**
 * \file    opencode_system.h
 * 
 * \brief   
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __OPENCODE_SYSTEM_H__
#define __OPENCODE_SYSTEM_H__


#include "common.h"


/**
 * @brief   에이전트가 실행 중인 배포판 정보
 */
typedef struct linux_distribution_system_informations
{
    /// Distribution ID
    mild_i8                     distrib_id[ STRLEN_32 ];

    /// Distribution ID like
    mild_i8                     distrib_id_like[ STRLEN_32 ];

    /// Distribution Name
    mild_i8                     distrib_name[ STRLEN_32 ];

    /// Distribution Version
    mild_i8                     distrib_version[ STRLEN_64 ];

    /// Distribution Version ID
    mild_i8                     distrib_version_id[ STRLEN_64 ];

    /// Distribution Pretty Name
    mild_i8                     distrib_pretty[ STRLEN_64 ];

    /// local ip address
    mild_i8                     local_ip[ STRLEN_24 ];

    /// local hostname
    mild_i8                     local_hostname[ STRLEN_64 ];

    /// local network interface card
    mild_i8                     local_nic[ STRLEN_32 ];

    /// current kernel version
    mild_i8                     kernel_version[ STRLEN_32 ];

} OPENCODE_SYSTEM_INFO, *POPENCODE_SYSTEM_INFO;


#endif  // #ifndef __OPENCODE_SYSTEM_H__
