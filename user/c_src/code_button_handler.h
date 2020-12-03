/**
 * \file    code_button_handler.h
 * 
 * \brief   에이전트의 버튼들을 처리하는 함수들
 * 
 * \date    2020.09.24.
 *          2020.12.04.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __CODE_BUTTON_HANDLER_H__
#define __CODE_BUTTON_HANDLER_H__


#include "common.h"

#include <gtk/gtk.h>


/**
 * @brief   설정 정보 버튼 처리기
 * 
 * @param   this__      설정 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void config_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


/**
 * @brief   시스템 정보 버튼 처리기
 * 
 * @param   this__      시스템 정보 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void system_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


/**
 * @brief   프로세스 정보 버튼 처리기
 * 
 * @param   this__      프로세스 정보 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void process_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


/**
 * @brief   proc 정보 버튼 처리기
 * 
 * @param   this__      proc 정보 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void proc_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


/**
 * @brief   시간 정보 버튼 처리기
 * 
 * @param   this__      시간 정보 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void time_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


/**
 * @brief   sysfs 정보 버튼 처리기
 * 
 * @param   this__      sysfs 정보 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void sysfs_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );


/**
 * @brief   netlinnk 정보 버튼 처리기
 * 
 * @param   this__      netlink 정보 버튼 위젯
 * @param   user_data__ 전달된 정보
 */
extern void netlink_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    );

#endif  // #ifndef __CODE_BUTTON_HANDLER_H__
