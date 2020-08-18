/**
 * \file    malog_handler.h
 * 
 * \brief   로그 파일 생성, 로그 기록 등의 작업을 수행
 *          에이전트 출력 설정에 따라 dprint( )에서 호출하여 로그를 기록하는 형식
 *          dprint( )이외의 로그 기록 인터페이스는 존재하지 않음
 * 
 * \date    2019.01.24.
 *          2020.07.09. modified by wikim.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__MALOG_HANDLER_H__
#define __LIB_UTILITY__MALOG_HANDLER_H__


#include "common.h"
#include "utility_definitions.h"


void cleanup_malog (
	mild_i32					*fd__
	);


#endif // #ifndef __LIB_UTILITY__MALOG_HANDLER_H__
