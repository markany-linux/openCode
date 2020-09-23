/**
 * \file    sysfs_handler.h
 * 
 * \brief   sysfs 커널 객체 및 핸들러 생성
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __SYSFS_HANDLER_H__
#define __SYSFS_HANDLER_H__


#include "kcommon.h"


/// sysfs에서 info 파일로 반환할 정보
extern SYSFS_INFO info;

/// sysfs 그룹 생성에 사용하기 위해 설정된 그룹
extern struct attribute_group openCode_attr_group;


#endif  // #ifndef __SYSFS_HANDLER_H__
