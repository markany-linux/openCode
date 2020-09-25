/**
 * \file    code_version.h
 * 
 * \brief   openCode 버전 정보
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __CODE_VERSION_H__
#define __CODE_VERSION_H__


#include "common.h"


/// openCode Major version
#define OPENCODE_MAJOR_VERSION          0
/// openCode minor version
#define OPENCODE_MINOR_VERSION          1
/// openCode patch version
#define OPENCODE_PATCH_VERSION          0
/// openCode custom version
#define OPENCODE_CUSTOM_VERSION         0

/// Current openCode version
#define OPENCODE_VERSION                MA_VERSION_MAKER(OPENCODE_MAJOR_VERSION,OPENCODE_MINOR_VERSION,OPENCODE_PATCH_VERSION,OPENCODE_CUSTOM_VERSION)


#endif  // #ifndef __CODE_VERSION_H__
