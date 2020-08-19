/**
 * \file    opencode_ui.h
 * 
 * \brief   UI를 위한 위젯 관리 정보
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@marknay.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __OPENCODE_UI_H__
#define __OPENCODE_UI_H__


#include "common.h"

#include <gtk/gtk.h>


/**
 * @brief   에이전트 관리 위젯
 */
typedef struct openCode_ui_widgets_needs_management
{
    /// main window
    GtkWidget                   *mainWindow;

    /// sysfs state image
    GtkWidget                   *sysfs_state;

    /// netlink state image
    GtkWidget                   *netlink_state;

    /// information label
    GtkWidget                   *info_label;

    /// information treeview
    GtkWidget                   *info_view;

    /// information store
    GtkTreeStore                *info_store;

    /// information iterator
    GtkTreeIter                 *info_iter;

} OPENCODE_UI, *POPENCODE_UI;


#endif  // #ifndef __OPENCODE_UI_H__
