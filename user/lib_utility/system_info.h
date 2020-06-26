/**
 * \file    system_info.h
 * 
 * \brief   리눅스 배포판과 시스템에 대한 정보를 획득
 *          * "/etc/os-release" 파일 파싱을 통한 배포판 정보 획득
 *          * 현재 활성화된 IP 주소와 hostname 및 NIC 이름 획득
 *          * 현재 커널 버전 획득
 * 
 * \date    2018.08.29.
 *          2020.06.26. modified by wikim
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__SYSTEM_INFO_H__
#define __LIB_UTILITY__SYSTEM_INFO_H__


#include "common.h"


/**
 * @brief   에이전트가 설치된 배포판 정보
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

} MADRM_LOCAL_SYSTEM, *PMADRM_LOCAL_SYSTEM;


/**
 * @brief   시스템과 배포판에 대한 정보를 획득하여 반환
 * 
 * @param   system__    획득된 정보를 반환할 구조체
 * 
 * @return  모든 정보 획득 성공 true, 실패 false
 */
extern mild_bool get_system_info(
    PMADRM_LOCAL_SYSTEM         system__
    );


#endif //>  #ifndef __LIB_UTILITY__SYSTEM_INFO_H__
