/**
 * \file    sysfs_init.h
 * 
 * \brief   sysfs 초기화 및 해제 인터페이스
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __SYSFS_INIT_H__
#define __SYSFS_INIT_H__


#include "kcommon.h"
#include "lkm_version.h"


/**
 * @brief   sysfs 커널 객체 초기화 및 등록
 * 
 * @param   netlink_load__  info 파일에 반환할 netlink 적재 상태
 * 
 * @return  초기화 및 등록 성공 true, 실패 false
 */
extern mild_bool initSysfsKernelObject(
    mild_bool                   netlink_load__
    );


/**
 * @brief   netlink 상태 변경
 *          * 현재 사용하지 않음
 * 
 * @param   netlink_load__  변경할 netlink 적재 상태
 */
extern void updateNetlinkLoadState(
    mild_bool                   netlink_load__
    );


/**
 * @brief   sysfs 커널 객체 해제
 */
extern void exitSysfsKernelObject( void );


#endif  // #ifndef __SYSFS_INIT_H__
