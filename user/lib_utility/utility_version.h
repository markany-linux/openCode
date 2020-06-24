/**
 * \file    utility_version.h
 * 
 * \brief   32bit version information structure
 *          Current config 32bit version DRM agent version setup info.
 *          * Major MAX: 15
 *          * minor MAX: 255
 *          * patch MAX: 1023
 *          * custom MAX: 1023
 * 
 *          1111 1111 1111 1111 1111 1111 1111 1111 : 32bit
 *          ^^^^ **** **** $$$$ $$$$ $$## #### ####
 *          ^ -> Major version value (4bit, MAX 15)
 *          * -> minor version value (8bit, MAX 255)
 *          $ -> patch version value (10bit, MAX 1023)
 *          # -> custom value (10bit, MAX 1023)
 * 
 *          ! more use custom value reduce patch value
 *          1111 1111 1111 1111 1111 1111 1111 1111 : 32bit
 *          ^^^^ **** **** $$$$ $$$$ #### #### ####
 *          ^ -> Major version value (4bit, MAX 15)
 *          * -> minor version value (8bit, MAX 255)
 *          $ -> patch version value (8bit, MAX 255)
 *          # -> custom value (12bit, MAX 4095)
 * 
 * \date    2020.06.24.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__UTILITY_VERSION_H__
#define __LIB_UTILITY__UTILITY_VERSION_H__


#include "common.h"


/// Major version make macro
#define MA_MAJOR_VERSION_MAKER(M)           ((mild_u32)M<<28)
/// minor version make macro
#define MA_MINOR_VERSION_MAKER(m)           ((mild_u32)m<<20)
/// patch version make macro. TODO: use less patch value to MAX 255, modify 10 to 12
#define MA_PATCH_VERSION_MAKER(p)           ((mild_u32)p<<10)
/// custom version make macro. TODO: use more custom value to MAX 4095, modify 3FF to FFF
#define MA_CUSTOM_VERSION_MAKER(c)          ((mild_u32)c&0x3FF)

/// 32bit version make macro
#define MA_VERSION_MAKER(M,m,p,c)           ((mild_u32)(MA_MAJOR_VERSION_MAKER(M)|\
                                            MA_MINOR_VERSION_MAKER(m)|\
                                            MA_PATCH_VERSION_MAKER(p)|\
                                            MA_CUSTOM_VERSION_MAKER(c)))


/// get Major version from all version value
#define MA_GET_MAJOR_VERSION(v)             ((mild_u32)v>>28)
/// get minor version from all version value
#define MA_GET_MINOR_VERSION(v)             ((mild_u32)(v<<4)>>24)
/// get patch version from all version value. TODO: use less patch value to MAX 255, modify 22 to 24
#define MA_GET_PATCH_VERSION(v)             ((mild_u32)(v<<12)>>22)
/// get custom version from all version value. TODO: use more custom value to MAX 4095, modify 3FF to FFF
#define MA_GET_CUSTOM_VERSION(v)            ((mild_u32)v&0x3FF)


/// Utility library major version
#define MA_UTILITY_MAJOR_VERSION            1
/// Utility library minor version
#define MA_UTILITY_MINOR_VERSION            0
/// Utility library patch version
#define MA_UTILITY_PATCH_VERSION            0
/// Utility library custom version
#define MA_UTILITY_CUSTOM_VERSION           0

/// Current Utility library version
#define MA_UTILITY_VERSION                  MA_VERSION_MAKER(MA_UTILITY_MAJOR_VERSION,MA_UTILITY_MINOR_VERSION,MA_UTILITY_PATCH_VERSION,MA_UTILITY_CUSTOM_VERSION)


#endif  // #ifndef __LIB_UTILITY__UTILITY_VERSION_H__
