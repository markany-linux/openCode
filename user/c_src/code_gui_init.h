/**
 * \file    code_gui_init.h
 * 
 * \brief   
 * 
 * \date    2020.09.24.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __C_SRC__CODE_GUI_INIT_H__
#define __C_SRC__CODE_GUI_INIT_H__


#include "common.h"

#include <gtk/gtk.h>


extern void setup_main_window(
    GtkWidget                   *main_window__
    );


extern void setup_agent_widgets(
    GtkWidget                   *mainBox__
    );


#endif  // #ifndef __C_SRC__CODE_GUI_INIT_H__
