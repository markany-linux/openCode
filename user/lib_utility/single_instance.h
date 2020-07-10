/**
 * \file    single_instance.h
 * 
 * \brief   에이전트 다중 실행 방지 기능
 *          전달 경로에 파일을 생성하고, 잠금 기능 적용
 *          에이전트 실행 시, 동일 위치 파일의 접근 불가 여부로 실행 여부 판단
 * 
 * \date    2018.05.09.
 *          2020.07.09. modified by wikim.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__SINGLE_INSTANCE_H__
#define __LIB_UTILITY__SINGLE_INSTANCE_H__


#include "common.h"
#include "utility_definitions.h"


/**
 * @brief   단일 실행을 위해 파일 생성 및 설정으로 다중 실행을 방지
 * 
 * @param   pathname__  생성할 잠금 파일 절대 경로명
 * 
 * @return  단일 실행 설정 완료 true, 실정 실패나 선행 실행된 에이전트가 존재하면 false
 */
extern mild_bool setup_single_instance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    );


/**
 * @brief   단일 실행을 위해 생성된 파일 설정을 제거하고 삭제
 * 
 * @param   pathname__  삭제할 잠금 파일 절대 경로명
 */
extern void cleanup_single_instance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    );


#endif  //> #ifndef __LIB_UTILITY__SINGLE_INSTANCE_H__
