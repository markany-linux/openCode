/**
 * \file    code_gui_init.h
 * 
 * \brief   GUI 구성을 위한 위젯 생성과 초기화
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


/**
 * @brief   최상위 윈도우 설정 및 초기화
 * 
 * @param   main_window__   초기화할 최상위 윈도우 위젯
 */
extern void setup_main_window(
    GtkWidget                   *main_window__
    );


/**
 * @brief   에이전트 위젯들을 생성하고 초기화
 * 
 * @param   mainBox__   
 */
extern void setup_agent_widgets(
    GtkWidget                   *mainBox__
    );


#endif  // #ifndef __C_SRC__CODE_GUI_INIT_H__
