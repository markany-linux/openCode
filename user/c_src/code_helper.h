/**
 * \file    code_helper.h
 * 
 * \brief   openCode 처리 도움 기능
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __CODE_HELPER_H__
#define __CODE_HELPER_H__


#include "agent_types.h"


/**
 * @brief   에이전트 관리 구조체 메모리 할당 및 초기화
 * 
 * @param   agent__ 관리 구조체
 * 
 * @return  메모리 할당 성공 true, 실패 false
 */
extern mild_bool malloc_code_agent(
    POPENCODE_AGENT             *agent__
    );


/**
 * @brief   에이전트 관리 구조체 메모리 초기화 및 해제
 * 
 * @param   agent__ 관리 구조체
 */
extern void free_code_agent(
    POPENCODE_AGENT             agent__
    );


/**
 * @brief   사용자 정보 획득 및 반환
 * 
 * @param   uid__   사용자 아이디
 * @param   user__  반환 구조체
 * 
 * @return  획득 및 반환 성공 true, 실패 false
 */
extern mild_bool set_user_info(
    mild_i32                    uid__,
    POPENCODE_USER              user__
    );


/**
 * @brief   sysfs 파일 개방 후, 내용을 읽어 반환
 *          * 항상 /sys/kernel/openCode/ 디렉터리 하위 파일을 개방하여 처리
 * 
 * @param   file__  개방할 파일명
 * @param   buf__   반환 버퍼
 * @param   len__   읽을 길이
 * 
 * @return  개방 성공 true, 실패 false
 */
extern mild_bool open_sysfs_get_contents(
    mild_cstr                   file__,
    mild_ptr                    buf__,
    mild_i32                    len__
    );


/**
 * @brief   netlink 연결
 * 
 * @param   fd__    획득하여 반환할 디스크립터
 * 
 * @return  연결 성공 true, 실패 false
 */
extern mild_bool connect_netlink(
    mild_i32                    *fd__
    );


/**
 * @brief   netlink를 통해 정보를 획득하여 반환
 * 
 * @param   fd__    netilnk에 연결된 디스크립터
 * @param   data__  획득하여 반환할 버퍼
 * 
 * @return  획득 성공 true, 실패 false
 */
extern mild_bool get_netlink_data(
    mild_i32                    fd__,
    PNETLINK_DATA               data__
    );


#endif  // #ifndef __CODE_HELPER_H__
