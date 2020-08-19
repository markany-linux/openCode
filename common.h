/**
 * \file    common.h
 * 
 * \brief   Define user/kernel common definitions and info. for openCode
 * 			"mild_" prefix means "Markany Interface for Linux Drm"
 * 
 * \date    2020.05.20.
 * 
 * \author  wikim (wikim@markany.com)
 */
#ifndef __COMMON_H__
#define __COMMON_H__


#include <sys/types.h>


/// defin nULL type
#define mild_null					(0)

/// define default numeric data types
typedef	char                        mild_i8;
typedef unsigned char               mild_u8;
typedef short                       mild_i16;
typedef unsigned short              mild_u16;
typedef	int                         mild_i32;
typedef unsigned int                mild_u32;
typedef long                        mild_long;
typedef unsigned long               mild_ulong;
typedef long long                   mild_i64;
typedef unsigned long long          mild_u64;
typedef float                       mild_float;
typedef double                      mild_double;
typedef size_t                      mild_size;

/**
@brief  define Boolean type and true, false value
*/
typedef enum mild_bool
{
	mild_false	= 0,

	mild_true	= 1

} mild_bool;

/// string type
typedef	char*                       mild_str;

/// unsigned string type
typedef unsigned char*              mild_ustr;

/// const string type
typedef const char*                 mild_cstr;

/// void pointer type
typedef void*                       mild_ptr;

/// const void pointer type
typedef const void*                 mild_cptr;


/**
 * @brief	Const Variable Length Define
 */
#define STRLEN_4                    4
#define STRLEN_8                    8
#define STRLEN_16                   16
#define STRLEN_24                   24
#define STRLEN_32                   32
#define STRLEN_48                   48
#define STRLEN_64                   64
#define STRLEN_128                  128
#define STRLEN_256                  256
#define STRLEN_512                  512
#define STRLEN_1024                 1024
#define STRLEN_2048                 2048
#define PAGESIZE                    4096
#define TWOPAGE                     8192

/**
 * @brief	SYSFS definitions
 */
#define SYSFS_HOME                  "/sys/kernel"
#define SYSFS_EXPORT_DIR            "openCode"
#define SYSFS_TARGET_FILE           SYSFS_HOME "/" SYSFS_EXPORT_DIR

/**
 * @brief	Netlink port number
 */
#define NETLINK_PORT_NUMBER         21


/**
 * @brief	32bit version information structure
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
 */

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

#endif  // #ifndef __COMMON_H__
