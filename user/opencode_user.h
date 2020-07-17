/**
 * \file    opencode_user.h
 * 
 * \brief   에이전트 사용자 정보
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __OPENCODE_USER_H__
#define __OPENCODE_USER_H__


#include "common.h"


/**
 * @brief   에이전트를 실행한 사용자 정보
 */
typedef struct current_user_information_who_execute_opencode_agent
{
    /// 사용자 아이디
    mild_i32                    user_id;

    /// 사용자 이름
    mild_i8                     user_name[ STRLEN_64 ];

    /// 사용자 홈 디렉터리
    mild_i8                     user_home[ STRLEN_64 ];

} OPENCODE_USER, *POPENCODE_USER;


#endif  // #ifndef __OPENCODE_USER_H__
