/**
 * \file    opencode_library.h
 * 
 * \brief   에이전트에서 로드하는 라이브러리 핸들 및 버전 정보 관리
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __OPENCODE_LIBRARY_H__
#define __OPENCODE_LIBRARY_H__


#include "common.h"

#include "../lib_utility/include/utility_interface.h"

/**
 * @brief   라이브러리 핸들 관리 구조체
 */
typedef struct opencode_load_library_handles
{
    /// 유틸리티 라이브러리 핸들
    void                        *lib_utility;

    /// 유틸리티 라이브러리 버전
    mild_u32                    lib_utility_version;

    /// config 처리 핸들
    PCONFIG_LIST                config_handle;

} OPENCODE_LIBRARY_HANDLE, *POPENCODE_LIBRARY_HANDLE;


#endif  // #ifndef __OPENCODE_LIBRARY_H__
