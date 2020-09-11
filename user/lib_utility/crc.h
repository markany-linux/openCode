/**
 * \file    crc.h
 * 
 * \brief   
 * 
 * \date    2019.09.19.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2019.
 */
#ifndef __LIB_UTILITY__CRC_H__
#define __LIB_UTILITY__CRC_H__


#include "utility_definitions.h"


/**
 * @brief   CRC 값 획득을 위한 메인 인터페이스
 *          * 내부적으로 update_crc( ) 호출로 획득
 * 
 * @param   buffer__    CRC 값 획득을 위한 버퍼
 * @param   len__       버퍼의 길이
 * 
 * @return  버퍼에서 획득된 CRC 값
 */
mild_u32 get_crc_value(
    mild_custr                  buffer__,
    mild_i32                    len__
    );


#endif  // #ifndef __LIB_UTILITY__CRC_H__
