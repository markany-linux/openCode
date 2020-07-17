/**
 * \file    agent_types.h
 * 
 * \brief   에이전트 사용 자료 구조 선언
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __AGENT_TYPES_H__
#define __AGENT_TYPES_H__


#include "opencode_control.h"
#include "opencode_sysfs.h"
#include "opencode_system.h"
#include "opencode_ui.h"


/**
 * @brief   openCode agent management info
 */
typedef struct openCode_agent_management_information
{
    mild_i32                    agent_pid;

    OPENCODE_CONTROL            control;

    OPENCODE_SYSFS_INFO         sysfs;

    OPENCODE_SYSTEM_INFO        system;

    OPENCODE_UI                 ui;

} OPENCODE_AGENT, *POPENCODE_AGENT;


#endif  // #ifndef __AGENT_TYPES_H__
