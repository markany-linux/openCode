/**
 * \file    lkm_version.h
 * 
 * \brief   
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LKM_VERSION_H__
#define __LKM_VERSION_H__

#include "kcommon.h"


/// lkm Major version
#define LKM_MAJOR_VERSION           0
/// lkm minor version
#define LKM_MINOR_VERSION           9
/// lkm patch version
#define LKM_PATCH_VERSION           0
/// lkm custom version
#define LKM_CUSTOM_VERSION          0
/// lkm version
#define LKM_VERSION                 MA_VERSION_MAKER(LKM_MAJOR_VERSION,LKM_MINOR_VERSION,LKM_PATCH_VERSION,LKM_CUSTOM_VERSION)


/// sysfs Major version
#define SYSFS_MAJOR_VERSION         0
/// sysfs minor version
#define SYSFS_MINOR_VERSION         9
/// sysfs patch version
#define SYSFS_PATCH_VERSION         0
/// sysfs custom version
#define SYSFS_CUSTOM_VERSION        1
/// sysfs version
#define SYSFS_VERSION               MA_VERSION_MAKER(SYSFS_MAJOR_VERSION,SYSFS_MINOR_VERSION,SYSFS_PATCH_VERSION,SYSFS_CUSTOM_VERSION)

/// netlink Major version
#define NETLINK_MAJOR_VERSION       0
/// netlink minor version
#define NETLINK_MINOR_VERSION       9
/// netlink patch version
#define NETLINK_PATCH_VERSION       2
/// netlink custom version
#define NETLINK_CUSTOM_VERSION      3
/// netlink version
#define NETLINK_VERSION             MA_VERSION_MAKE(NETLINK_MAJOR_VERSION,NETLINK_MINOR_VERSION,NETLINK_PATCH_VERSION,NETLINK_CUSTOM_VERSION)


#endif  // #ifndef __LKM_VERSION_H__