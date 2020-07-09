/**
 * \file    malog_handler.h
 * 
 * \brief   로그 파일 생성, 로그 기록 등의 작업을 수행
 *          에이전트 출력 설정에 따라 dprint( )에서 호출하여 로그를 기록하는 형식
 *          dprint( )이외의 로그 기록 인터페이스는 존재하지 않음
 * 
 * \date    2019.01.24.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2019.
 */
#ifndef __LIB_UTILITY__MALOG_HANDLER_H__
#define __LIB_UTILITY__MALOG_HANDLER_H__


#include "utility_common.h"


extern mild_bool init_malog(
    mild_cstr                   path__
    );


extern mild_bool malog_dprint_write(
    mild_cstr                   msg__
    );


extern void cleanup_malog( void );


#endif // #ifndef __LIB_UTILITY__MALOG_HANDLER_H__
