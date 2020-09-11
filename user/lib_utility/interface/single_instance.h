/**
 * \file    interface/single_instance.h 인터페이스 정의
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  swma (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__SINGLE_INSTANCE_IMPL_H__
#define __LIB_UTILITY__SINGLE_INSTANCE_IMPL_H__


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////////////////
//
// single_instance.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


extern mild_bool setupSingleInstance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    );


extern void cleanupSingleInstance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    );


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__SINGLE_INSTANCE_IMPL_H__
