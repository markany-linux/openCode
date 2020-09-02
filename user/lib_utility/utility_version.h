/**
 * \file    utility_version.h
 * 
 * \brief   유틸리티 라이브러리 버전 설정
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
