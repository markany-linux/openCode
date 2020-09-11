/**
 * \file    interface/lib_utility.h
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  wikim (wikim@markany.com), swma (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
#define __LIB_UTILITY__UTILITY_INTERFACE_H__


#include "common.h"

#include "file_check.h"
#include "time_handler.h"
#include "proc_handler.h"
#include "string_parser.h"
#include "system_info.h"
#include "config_handler.h"


#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////////////////
//
// utility_init.c 인터페이스 정의
//  * 현재(2020.06.24) 라이브러리 버전을 획득하는 인터페이스만 존재
//
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief	유틸리티 라이브러리 버전 반환
 * 
 * @return	라이브러리 버전
 */
extern mild_u32 getMaUtilityLibraryVersion( void );


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
