/**
 * \file    sysfs_init.h
 * 
 * \brief   
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


extern mild_bool initSysfsKernelObject(
    mild_bool                   netlink_load__
    );


extern void updateNetlinkLoadState(
    mild_bool                   netlink_load__
    );


extern void exitSysfsKernelObject( void );


#endif  // #ifndef __SYSFS_INIT_H__
