/**
 * \file	time_handler.h
 * 
 * \brief	get time or date info. with number or string interface
 *
 * \date	2017.6.30.
 * 			2020.07.09. modified by wikim.
 * 
 * \author	wikim (wikim@markany.com)
 *
 * \copyright MarkAny Inc. 2020.
*/
#ifndef __LIB_UTILITY__TIME_HANDLER_H__
#define __LIB_UTILITY__TIME_HANDLER_H__


#include <time.h>

#include "common.h"


/**
 * @brief   현재 타임 스템프 정보 획득 및 반환
 *          * 년월일시분초까지만 획득 -> 201903051822
 *          * 버퍼는 최소 STRLEN_24 이상. 아이디 없으면 24가 적당
 * 
 * @param   stamp__ 타임 스템프 반환 버퍼
 * 
 * @return  획득 및 반환 성공 true, 실패 false
 */
extern mild_bool get_current_timestamp(
    mild_str                    stamp__
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
extern mild_bool get_current_timestamp_mn(
	mild_str					stamp__
	);


/**
 * @brief	현재 시간 정보를 숫자 형태로 반환
 * 
 * @param	cur_time__	반환할 숫자 형태의 시간
 * 
 * @return	시간 획득 성공 true, 실패 false
 */
extern mild_bool get_current_time(
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
extern void get_time_readable(
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
extern void get_date_readable(
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
extern void get_date_time_readable(
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
extern mild_bool get_current_time_readable(
	mild_str					buf__
	);


/**
 * @brief	오늘 날짜를 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool get_current_date_readable(
	mild_str					buf__
	);


/**
 * @brief	현재 날짜/시간을 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool get_current_date_time_readable(
	mild_str					buf__
	);


/**
 * @brief	전달 시간을 표준 출력
 * 
 * @param	time__		출력할 시간
 * @param	linefeed__	시간 출력 후, 줄 바꿈 여부
 */
extern void disp_time(
	mild_u64					time__,
	mild_bool					linefeed__
	);


/**
 * @brief	전달 날짜를 표준 출력
 * 
 * @param	time__		출력할 시간
 * @param	linefeed__	날짜 출력 후, 줄 바꿈 여부
 */
extern void disp_date(
	mild_u64					time__,
	mild_bool					linefeed__
	);


/**
 * @brief	전달 시간의 날짜와 시간을 표준 출력
 * 
 * @param	time__	출력할 시간
 */
extern void disp_date_time(
	mild_u64					time__
	);


#endif	//> #ifndef __LIB_UTILITY__TIME_HANDLER_H__
