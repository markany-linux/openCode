/**
 * \file    file_check.h
 * 
 * \brief   
 * 
 * \date    2020.05.26.
 * 
 * \author  wikim (wikim@markany.com)
 */
#ifndef __LIB_UTILITY__FILE_CHECK_H__
#define __LIB_UTILITY__FILE_CHECK_H__


#include "common.h"


/**
 * @brief   file check main function using access( )
 * 
 * @param   pathname__  check file pathname
 * @param   mode__      check mode
 * 
 * @return  request check success true, else false
 */
extern mild_bool check_file_with_mode(
    mild_cstr                   pathname__,
    mild_i32                    mode__
    );


#endif  // #ifndef __LIB_UTILITY__FILE_CHECK_H__
