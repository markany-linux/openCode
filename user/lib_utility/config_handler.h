/**
 * \file    config_handler.h
 * 
 * \brief   에이전트 동작 설정 파일을 읽어 리스트로 관리
 *          * agent.conf 파일을 현재 디렉터리에서 찾아 처리
 *          * 파일에 label = value 형태로 구성된 모든 항목을 획득
 *          * 값을 획득할 때는 label만 전달하여 획득하는 형태
 *           - label이 존재하지 않을 때, 실패를 반환
 *          FIXME: 현재 중복 값 처리되지 않는지 확인하고 처리 필요
 * 
 * \date    2019.01.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2019.
 */
#ifndef __LIB_UTILITY__CONFIG_HANDLER_H__
#define __LIB_UTILITY__CONFIG_HANDLER_H__


#include "utility_definitions.h"
#include "gpl_list.h"

#include "interface/lib_utility.h"


/**
 * @brief   파일을 읽어 획득된 모든 설정 정보의 출력
 */
void disp_config_list(
    PCONFIG_LIST                list__
    );


/**
 * @brief   설정 파일을 읽고, 파싱하여 리스트로 모든 정보를 획득하는 함수
 * 
 * @param   pathname__  설정 파일 경로
 * 
 * @return  파일 존재/읽어서 파싱이 모두 성공 true, 실패 false
 */
mild_bool init_config_list(
    PCONFIG_LIST                list__,
    mild_cstr                   pathname__
    );


/**
 * @brief   획득된 리스트에서 특정 설정 정보 값을 요청
 * 
 * @param   label__ 획득하려는 설정 라벨
 * @param   value__ 설정 라벨의 값을 반환 받을 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  설정 존재 및 반환 성공 true, 존재하지 않음 false
 */
mild_bool get_config_list_value(
    PCONFIG_LIST                list__,
    mild_cstr                   label__,
    mild_str                    value__,
    mild_u32                    len__
    );


/**
 * @brief   리스트의 모든 노드와 리스트 제거
 *
 * @param   list__  대상 리스트
 */
void cleanup_config_list(
    PCONFIG_LIST                list__
);


/**
 * @brief   설정 리스트 생성
 *
 * @param   list__  생성되는 리스트를 반환받을 변수
 */
mild_bool create_config_list(
    PCONFIG_LIST                *list__
    );


/**
 * @brief   설정 리스트 제거
 *
 * @param   list__  대상 리스트
 */
void destroy_config_list(
    PCONFIG_LIST                list__
    );


/**
 * @brief   설정 라벨과 값을 리스트에 추가
 * 
 * @param   label__ 추가할 설정 라벨
 * @param   value__ 추가할 설정 값
 * 
 * @return  리스트 추가 성공 true, 실패 false
 */
mild_bool add_config_list(
    PCONFIG_LIST                list__,
    mild_str                    label__,
    mild_str                    value__
    );


#endif // #ifndef __LIB_UTILITY__CONFIG_HANDLER_H__
