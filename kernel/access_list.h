/**
 * \file    access_list.h
 * 
 * \brief   sysfs 파일 접근 정보 관리 리스트 및 인터페이스
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __ACCESS_LIST_H__
#define __ACCESS_LIST_H__


#include "kcommon.h"


/**
 * @brief   새로운 리스트 노드 추가 인터페이스
 *          * sysfs 접근 정보를 리스트에 추가
 * 
 * @param   file__  접근한 sysfs 파일명
 * 
 * @return  노드 추가 성공 true, 실패 false
 */
extern mild_bool addNewAccessList(
    mild_str                    file__
    );


/**
 * @brief   리스트에 노드가 존재하는지 여부를 반환
 * 
 * @return  노드가 존재 true, 존재하지 않음 false
 */
extern mild_bool checkAccessListRemain( void );


/**
 * @brief   리스트에서 노드를 하나 획득
 *          * 획득된 노드는 동적 할당된 메모리로 사용 후 반드시 해제해야 함
 * 
 * @param   data__  반환할 노드
 * 
 * @return  노드 반환 성공 true, 실패 false
 */
extern mild_bool getAccessList(
    PNETLINK_DATA               *data__
    );


/**
 * @brief   리스트에 존재하는 모든 노드를 제거
 *          * 모듈 정리 시점에 호출하여 남아 있을 수 있는 노드를 모두 제거
 */
extern void cleanupAccessList( void );


#endif  // #ifndef __ACCESS_LIST_H__
