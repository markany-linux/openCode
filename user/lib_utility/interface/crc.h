/**
 * \file    interface/crc.h 인터페이스 정의
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 * 
 * \author  swma (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__CRC_IMPL_H__
#define __LIB_UTILITY__CRC_IMPL_H__


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////////////////
//
// crc.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   CRC 값 획득을 위한 메인 인터페이스
 *          * 내부적으로 update_crc( ) 호출로 획득
 * 
 * @param   buffer__    CRC 값 획득을 위한 버퍼
 * @param   len__       버퍼의 길이
 * 
 * @return  버퍼에서 획득된 CRC 값
 */
extern mild_u32 getCRCValue(
    mild_custr                  buffer__,
    mild_i32                    len__
    );


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__CRC_IMPL_H__
