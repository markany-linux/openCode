/**
 * \file    interface/config_handler.h 인터페이스 정의
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  MaBling (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__CONFIG_HANDLER_IMPL_H__
#define __LIB_UTILITY__CONFIG_HANDLER_IMPL_H__


#include <pthread.h>


#include "common.h"

#include "../gpl_list.h"

#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////////////////
//
// config_handler.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   config 리스트 관리 구조체
 */
typedef struct config_list_info
{
    /// 리스트 관리를 위한 헤드
    struct list_head            list_head;
    /// 리스트 동기화 제어를 위한 동기화 멤버
    pthread_mutex_t             list_lock;
} CONFIG_LIST, *PCONFIG_LIST;


/**
 * @brief   설정 라벨과 정보 보관 구조체
 */
typedef struct agent_configuration_info
{
    /// 설정 라벨
    mild_i8                     label[ STRLEN_32 ];

    /// 설정 값
    mild_i8                     value[ STRLEN_64 ];

    /// 이중 연결 리스트 포인터
    struct list_head            ptr;

} AGENT_CONFIG, *PAGENT_CONFIG;


/**
 * @brief   설정 리스트 생성
 *
 * @param   list__  생성되는 리스트를 반환받을 변수
 */
extern mild_bool createConfigList(
    PCONFIG_LIST                *list__
    );


/**
 * @brief   설정 리스트 제거
 *
 * @param   list__  대상 리스트
 */
extern void destroyConfigList(
    PCONFIG_LIST                list__
    );

/**
 * @brief   리스트의 모든 노드와 리스트 제거
 *
 * @param   list__  대상 리스트
 */
extern void cleanupConfigList(
    PCONFIG_LIST                list__
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
extern mild_bool getConfigListValue(
    PCONFIG_LIST                list__,
    mild_cstr                   label__,
    mild_str                    value__,
    mild_u32                    len__
    );


/**
 * @brief   설정 파일을 읽고, 파싱하여 리스트로 모든 정보를 획득하는 함수
 * 
 * @param   pathname__  설정 파일 경로
 * 
 * @return  파일 존재/읽어서 파싱이 모두 성공 true, 실패 false
 */
extern mild_bool initConfigList(
    PCONFIG_LIST                list__,
    mild_cstr                   pathname__
    );


/**
 * @brief   파일을 읽어 획득된 모든 설정 정보의 출력
 */
extern void dispConfigListValue(
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
extern mild_bool addConfigList(
    PCONFIG_LIST                list__,
	mild_str					label__,
	mild_str					value__
	);


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__CRC_IMPL_H__
