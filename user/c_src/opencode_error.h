/**
 * \file    opencode_error.h
 * 
 * \brief   
 * 
 * \date    2020.08.06.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __HEADERS__OPENCODE_ERROR_H__
#define __HEADERS__OPENCODE_ERROR_H__


#include "common.h"


/**
 * @brief   오류 메시지 번호 선언
 */
typedef enum openCode_error_init_number_definitions
{

    OPENCODEERROR_INIT_UNKONWN                      =   0,

    OPENCODEERROR_INIT_SINGLE_INSTANCE              =   1,

    OPENCODEERROR_INIT_MEMORY_ALLOCATION            =   2,

    OPENCODEERROR_INIT_USER_INFO                    =   3

} OPENCODE_ERROR, *POPENCODE_ERROR;


/**
 * @brief   오류 메시지 대응 문자열
 */
static const mild_i8 g_init_error_msg[ ][ STRLEN_128 ] = {
    "Unknown error occur in init process",
    "Set single instance fail",
    "Memory allocation fail for agent",
    "Fail to get user information"
    };


#endif  // #ifndef __HEADERS__OPENCODE_ERROR_H__
