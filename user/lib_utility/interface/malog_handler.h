/**
 * \file    interface/malog_handler.h 인터페이스 정의
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  MaBling (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__MALOG_HANDLER_IMPL_H__
#define __LIB_UTILITY__MALOG_HANDLER_IMPL_H__


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////////////////
//
// malog_handler.c/h 인터페이스 정의
//  * 로그 파일 생성, 로그 기록 등의 작업을 수행
//  * 에이전트 출력 설정에 따라 dprint( )에서 호출하여 로그를 기록하는 형식
//  * dprint( )이외의 로그 기록 인터페이스는 존재하지 않음
//
///////////////////////////////////////////////////////////////////////////////


extern mild_bool initLogFile(
    mild_i32                    *fd__,
    mild_cstr                   pathname__,
    mild_cstr                   dir_name__
    );


extern mild_bool writeLogFile(
    mild_i32                    fd__,
    mild_cstr                   log__
    );


extern void closeLogFile(
    mild_i32                    *fd__
    );


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__MALOG_HANDLER_IMPL_H__
