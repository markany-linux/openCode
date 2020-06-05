/**
 * \file    utility_interface.h
 * 
 * \brief   
 * 
 * \date    2020.06.02.
 * 
 * \author  wikim (wikim@markany.com)
 */
#ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
#define __LIB_UTILITY__UTILITY_INTERFACE_H__


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief   check if file exist
 * 
 * @param   pathname__  file path-name
 * 
 * @return  if file exist true, not false
 */
extern mild_bool checkFileExist(
    mild_cstr                   pathname__
    );


/**
 * @brief   check if can read file
 * 
 * @param   pathname__  file path-name
 * 
 * @return  if read permission exist true, not false
 */
extern mild_bool checkFileReadPerm(
    mild_cstr                   pathname__
    );


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
