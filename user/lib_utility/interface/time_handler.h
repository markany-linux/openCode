/**
 * \file    interface/time_handler.c
 * 
 * \brief   시간 정보 획득을 위한 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  swma (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__TIME_HANDLER_IMPL_H__
#define __LIB_UTILITY__TIME_HANDLER_IMPL_H__


#include <bits/types/clock_t.h>


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief   시간 측정을 위한 구조체
 */
typedef struct time_interval_info_for_check_performace
{
    /// 측정 시작 시간
    mild_long                   start;

    /// 측정 종료 시간
    mild_long                   end;

} TIME_INTERVAL, *PTIME_INTERVAL;


/**
 * @brief	코드 동작 시간 정보 처리를 위한 정보 구조체
 */
typedef struct app_execution_time_check_info
{
	/// 코드 동작 시간 측정을 위한 시작 시간
	clock_t						app_start;

	/// 코드 동작 시간 측정을 위한 종료 시간
	clock_t						app_end;

	/// 시작 시간 설정 여부
	mild_bool					set_app;

} APP_TIME, *PAPP_TIME;


extern mild_bool getCurrentTimestamp(
	mild_str					stamp__
	);


extern mild_bool getCurrentTimestampMn(
	mild_str					stamp__
	);


extern mild_bool getCurrentTime(
	mild_u64					*time__
	);


extern void getTimeReadable(
	mild_u64					time__,
	mild_str					buf__
	);


extern void getDateReadable(
	mild_u64					time__,
	mild_str					buf__
	);


extern void getDateTimeReadable(
	mild_u64					current__,
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	);


extern mild_bool getCurrentTimeReadable(
	mild_str					buf__
	);


extern mild_bool getCurrentDateReadable(
	mild_str					buf__
	);


extern mild_bool getCurrentDateTimeReadable(
	mild_str					buf__
	);


extern void dispTimeReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	);


extern void dispDateReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	);


extern void dispDateTimeReadable(
	mild_u64					time__
	);


extern void setAppStartTime(
	PAPP_TIME					app_time__
	); 


extern mild_float setAppEndTime(
	PAPP_TIME					app_time__
	);


/**
 * @brief	시간 차이 측정 시작, 종료 시에 호출하는 함수
 * 			* 종료 시에는 획득된 정보를 기반으로 차이 값을 표준 출력
 * 
 * @param	label__	시간 측정 종료 시에 출력할 문자열. NULL 허용
 * @param	ti__	시간 구조체
 * @param	start__	측정 시작 여부
 */
extern void setTimeInterval(
    PAPP_TIME                   app_time__,
	mild_cstr					label__,
	mild_bool					start__
	);


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__TIME_HANDLER_IMPL_H__
