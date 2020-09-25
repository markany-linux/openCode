/**
 * \file    code_init.h
 * 
 * \brief   openCode 초기화 및 정리 인터페이스
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __CODE_INIT_H__
#define __CODE_INIT_H__


#include "agent_types.h"
#include "../lib_utility/include/utility_interface.h"


extern POPENCODE_AGENT g_agent;


/**
 * @brief   openCode 에이전트 초기화
 *          * 관리 구조체 메모리를 할당 받고, 초기화 작업 수행
 * 
 * @param   agent__ 관리 구조체
 * 
 * @return  초기화 성공 true, 실패 false
 */
extern mild_bool init_opencode_agent(
    POPENCODE_AGENT             *agent__
    );


/**
 * @brief   openCode 에이전트 정리
 *          * 정리 작업 수행 후, 관리 구조체 메모리 해제
 */
extern void cleanup_opencode_agent( void );


#endif  // #ifndef __CODE_INIT_H__
