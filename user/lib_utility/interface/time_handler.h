/**
 * \file    interface/time_handler.h
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


/**
 * @brief   현재 타임 스템프 정보 획득 및 반환
 *          * 년월일시분초까지만 획득 -> 201903051822
 *          * 버퍼는 최소 STRLEN_24 이상. 아이디 없으면 24가 적당
 * 
 * @param   stamp__ 타임 스템프 반환 버퍼
 * 
 * @return  획득 및 반환 성공 true, 실패 false
 */
extern mild_bool getCurrentTimestamp(
	mild_str					stamp__
	);


/**
 * @brief   현재 타임 스템프 정보 획득 및 반환
 *          * 년월일시분초밀나 정보 획득 -> 2019030518236721
 * 			* 버퍼는 최소 STRLEN_24 이상. 아이디까지 계산하면 64가 적당
 * 
 * @param   stamp__ 타임 스템프 반환 버퍼
 * 
 * @return  획득 및 반환 성공 true, 실패 false
 */
extern mild_bool getCurrentTimestampMn(
	mild_str					stamp__
	);


/**
 * @brief	현재 시간 정보를 숫자 형태로 반환
 * 
 * @param	cur_time__	반환할 숫자 형태의 시간
 * 
 * @return	시간 획득 성공 true, 실패 false
 */
extern mild_bool getCurrentTime(
	mild_u64					*time__
	);


/**
 * @brief	인수의 시간 정보를 읽을 수 있는 형태로 변환 및 반환
 * 			인수에서 시간 정보만을 변환
 * 			! 버퍼는 10 바이트 이상을 전달해야 함
 * 
 * @param	time__	변환할 시간 값
 * @param	buf__	변환 정보를 반환할 버퍼
 */
extern void getTimeReadable(
	mild_u64					time__,
	mild_str					buf__
	);


/**
 * @brief	인수의 시간 정보를 읽을 수 있는 형태로 변환 및 반환
 * 			인수에서 날짜 정보만을 변환
 * 			! 버퍼는 10 바이트 이상을 전달해야 함
 * 
 * @param	time__	변화할 시간 값
 * @param	buf__	변환 정보를 반환할 버퍼
 */
extern void getDateReadable(
	mild_u64					time__,
	mild_str					buf__
	);


/**
 * @brief	인수의 시간 정보를 읽을 수 있는 형태로 변환 및 반환
 * 			인수에서 날짜/시간을 선택적으로 변환 가능
 * 			! 버퍼는 요청에 따라 전달해야 함
 * 
 * @param	current__	변환할 시간 값
 * @param	buf__		변환 정보를 반환할 버퍼
 * @param	date__		날짜 변환 및 반환 여부
 * @param	time__		시간 변환 및 반환 여부
 */
extern void getDateTimeReadable(
	mild_u64					current__,
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	);


/**
 * @brief	현재 시간을 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool getCurrentTimeReadable(
	mild_str					buf__
	);


/**
 * @brief	오늘 날짜를 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool getCurrentDateReadable(
	mild_str					buf__
	);


/**
 * @brief	현재 날짜/시간을 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool getCurrentDateTimeReadable(
	mild_str					buf__
	);


/**
 * @brief	전달 시간을 표준 출력
 * 
 * @param	time__		출력할 시간
 * @param	linefeed__	시간 출력 후, 줄 바꿈 여부
 */
extern void dispTimeReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	);


/**
 * @brief	전달 날짜를 표준 출력
 * 
 * @param	time__		출력할 시간
 * @param	linefeed__	날짜 출력 후, 줄 바꿈 여부
 */
extern void dispDateReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	);


/**
 * @brief	전달 시간의 날짜와 시간을 표준 출력
 * 
 * @param	time__	출력할 시간
 */
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
