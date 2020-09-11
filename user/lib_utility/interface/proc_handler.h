/**
 * \file    interface/proc_handler.h 인터페이스 정의
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  swma (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__PROC_HANDLER_IMPL_H__
#define __LIB_UTILITY__PROC_HANDLER_IMPL_H__


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////////////////
//
// proc_handler.c/h 인터페이스 정의
//  * "/proc/modules" 파일에서 특정 모듈 존재 여부 확인
//  * "/proc/kallsyms" 파일에서 특정 커널 심볼 존재 여부 확인 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   "/proc/modules" 파일에서 특정 모듈 존재 여부 확인
 *          Ex. "/proc/modules" 파일 내용의 구성
 *          모듈 이름 | 크기 | 참조 | 참조 모듈 리스트                  | 상태 | 주소
 *          bluetooth 544768 29 rfcomm,bnep,btusb,btrtl,btbcm,btintel, Live 0xffffffffc0f96000
 * 
 * @param	module_name__	찾고자 하는 모듈 이름
 * 
 * @return  모듈이 발견되는 경우 true, 발견되지 않는 경우 false
 */
extern mild_bool checkKernelModuleExist(
	mild_cstr					target__
	);


/**
 * @brief   "/proc/kallsyms" 파일에서 특정 커널 심볼 존재 여부 확인
 *          Ex. "/proc/kallsyms" 파일 내용의 구성
 *          주소          | 형식 | 심볼 이름
 *          ffffffff9ac515d0 T sys_open
 * 
 * @param	symbol__	찾고자 하는 심볼 이름
 * @param	addr__		주소를 얻고자 할때, 전달
 * 
 * @return  심볼이 존재할 경우 true, 존재하지 않는 경우 false
 */
extern mild_bool checkKernelSymbolExist(
	mild_cstr					symbol__,
	mild_u64					*addr__
	);


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__PROC_HANDLER_IMPL_H__
