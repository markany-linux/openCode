/**
 * \file    common.h
 * 
 * \brief   Define user/kernel common definitions and communication info.
 * 
 * \date    2020.05.20.
 * 
 * \author  wikim (wikim@markany.com)
 */
#ifndef __COMMON_H__
#define __COMMON_H__


//////////////////////////////// Data type definitions

/// null
#define mild_null                               (0)

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


//////////////////////////////// Const Variable Length Define
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

/////////////////////////////// SYSFS definitions
#define SYSFS_HOME                  "/sys/kernel"
#define SYSFS_EXPORT_DIR            "openCode"
#define SYSFS_TARGET_FILE           SYSFS_HOME "/" SYSFS_EXPORT_DIR


/////////////////////////////// Netlink port number
#define NETLINK_PORT_NUMBER         21


#endif  // #ifndef __COMMON_H__
