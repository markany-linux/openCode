/**
 * \file    access_list.h
 * 
 * \brief   
 * 
 * \date    2020.09.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __ACCESS_LIST_H__
#define __ACCESS_LIST_H__


#include "kcommon.h"


extern mild_bool addNewAccessList(
    mild_str                    file__
    );


extern mild_bool checkAccessListRemain( void );


extern mild_bool getAccessList(
    PNETLINK_DATA               *data__
    );


extern void cleanupAccessList( void );


#endif  // #ifndef __ACCESS_LIST_H__
