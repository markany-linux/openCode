/**
 * \file    string_parser.h
 * 
 * \brief   각종 문자열 파싱을 위한 기능들
 * 
 * \date    2019.01.16.
 *          2020.06.25. modified by wikim.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__STRING_PARSER_H__
#define __LIB_UTILITY__STRING_PARSER_H__


#include "common.h"


// TODO: 길이를 받는 경우, 확인 범위가 길이를 초과하는지 확인해야 함


/**
 * @brief   버퍼에서 특정 문자열이 존재할 때, 시작 위치 변위 값을 반환
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  현재 위치에서 이동해야 할 변위. 없는 경우 -1
 */
extern mild_i32 get_target_string_offset(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 문자열 시작 위치의 포인터를 찾아 반환
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  시작 위치 포인터, 찾지 못한 경우 NULL
 */
extern mild_str get_target_string_ptr(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에 문자열 존재 여부만을 확인하고 반환
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  문자열이 존재하면 true, 존재하지 않으면 false
 */
extern mild_bool check_target_string_exist(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 단일 문자 시작 위치를 찾아 변위 값 반환
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  이동해야 할 변위. 없는 경우 -1
 */
extern mild_i32 get_target_char_offset(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 단일 문자 시작 위치 포인터를 찾아 반환
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  문자 위치 포인터, 존재하지 않으면 NULL
 */
extern mild_str get_target_char_ptr(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에 단일 문자 존재 여부 반환
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  문자가 존재하면 true, 존재하지 않으면 false
 */
extern mild_bool check_target_char_exist(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 다음 라인('\n')까지의 변위 값을 찾아 반환
 *          현재 위치에서 바로 다음 '\n' 까지 변위를 찾음
 * 
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  이동해야 할 변위. 없는 경우 -1
 */
extern mild_i32 get_next_line_offset(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 다음 라인 시작 위치 포인터를 찾아 반환
 *          현재 위치에서 바로 다음 '\n' 위치를 찾음
 * 
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  다음 라인 위치 포인터. 없는 경우 NULL
 */
extern mild_str get_next_line_ptr(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 현재 라인의 시작 위치 변위 값 반환
 *          바로 이전 '\n' 값을 찾음
 *          ! 이전에 '\n'이 존재하지 않으면 포인터 예외 오류가 발생하므로 주의 !
 * 
 * @param   buf__   버퍼의 현재 위치
 * 
 * @return  바로 이전 '\n' 까지 변위 값
 */
extern mild_i32 get_current_line_start_offset(
    mild_cstr                   buf__
    );


/**
 * @brief   버퍼에서 현재 라인 시작 위치 포인터 반환
 * 
 * @param   buf__   버퍼의 현재 위치
 * 
 * @return  바로 이전 '\n' 위치 포인터
 */
extern mild_str get_current_line_start_ptr(
    mild_cstr                   buf__
    );


/**
 * @brief   버퍼에서 다음 위치의 공백 위치 변위를 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * @param   len__   버퍼 길이
 * 
 * @return  다음 공백까지 변위. 존재하지 않으면 -1
 */
extern mild_i32 get_next_space_offset(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 다음 위치의 공백 위치 포인터 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * @param   len__   버퍼 길이
 * 
 * @return  다음 공백의 시작 위치 포인터. 존재하지 않으면 NULL
 */
extern mild_str get_next_space_ptr(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 이전 위치의 공백 위치 변위를 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * 
 * @return  이전 공백까지의 변위
 */
extern mild_i32 get_previous_space_offset(
    mild_cstr                   buf__
    );


/**
 * @brief   버퍼에서 이전 위치의 공백 위치 포인터 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * 
 * @return  이전 공백 위치 포인터
 */
extern mild_str get_previous_space_ptr(
    mild_cstr                   buf__
    );


/**
 * @brief	버퍼에서 첫 번째로 공백까지의 문자 개수를 반환
 * 			! 버퍼의 시작 위치가 공백인 경우, 0이 반환되므로 주의해야 함
 *          FIXME: getNextSpaceOffset( )으로 대체하면 제거해야 함
 * 
 * @param	str__	확인할 버퍼
 * 
 * @return	문자의 개수
 */
extern mild_u32 get_space_pos(
	mild_str					str__
	);


/**
 * @brief   다음 라인(\n)으로 현재 포인터를 이동시키는 함수
 * 
 * @param   ptr__   다음 라인으로 이동할 포인터
 * 
 * @return  다음 라인까지의 변위
 */
extern mild_i32 current_line_skip(
    mild_str                    *ptr__
    );


#endif // #ifndef __LIB_UTILITY__STRING_PARSER_H__
