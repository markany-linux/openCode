/**
 * \file    code_definitions.h
 * 
 * \brief   openCode에서 사용하는 각종 값들을 선언
 * 
 * \date    2020.07.17.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyright MarkAny Inc. 2020.
 */
#ifndef __CODE_DEFINITIONS_H__
#define __CODE_DEFINITIONS_H__


#include "common.h"


#define OPENCODE_TMP_DIR                    "/tmp"

#define MAINWINDOW_TITLE                    "openCode User Agent"
#define MAINWINDOW_WIDTH                    550
#define MAINWINDOW_HEIGHT                   400
#define MAINWINDOW_BORDER                   10

#define SINGLE_INSTANCE_NAME                OPENCODE_TMP_DIR "/openCode.pid" 

#define CONFIG_SERVER_IP                    "SERVER_IP"
#define CONFIG_PORT                         "PORT"


#endif  // #ifndef __CODE_DEFINITIONS_H__
