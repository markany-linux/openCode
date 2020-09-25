/**
 * \file    code_button_handler.h
 * 
 * \brief   
 * 
 * \date    2020.09.24.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __CODE_BUTTON_HANDLER_H__
#define __CODE_BUTTON_HANDLER_H__


#include "common.h"

#include <gtk/gtk.h>


extern void config_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );

extern void system_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


extern void process_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


extern void proc_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


extern void time_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


extern void sysfs_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


extern void netlink_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );

#endif  // #ifndef __CODE_BUTTON_HANDLER_H__
