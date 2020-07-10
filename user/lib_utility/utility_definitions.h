/**
 * \file    utility_definitions.h
 * 
 * \brief   유틸리티 공용 선언
 * 
 * \date    2020.07.10.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright Mark Inc. 2020.
 */
#ifndef __LIB_UTILITY__UTILITY_DEFINITIONS_H__
#define __LIB_UTILITY__UTILITY_DEFINITIONS_H__


#include "common.h"


/// 유효 파일 디스크립터 시작 번호
#define FD_START                        3

/// 기본 로그 디렉터리 이름
#define DEFAULT_LOG_DIR_NAME            "logs"

/// "/proc" file system access define
#define PROC_READ_LEN			PAGESIZE
#define PROC_MODULE_FILE		"/proc/modules"
#define PROC_SYSCALL_FILE		"/proc/kallsyms"


#endif  // #ifndef __LIB_UTILITY__UTILITY_DEFINITIONS_H__
