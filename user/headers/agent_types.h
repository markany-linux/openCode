/**
 * \file    agent_types.h
 * 
 * \brief   에이전트 관리 자료 구조 선언
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
#include "opencode_library.h"
#include "opencode_sysfs.h"
#include "opencode_system.h"
#include "opencode_ui.h"
#include "opencode_user.h"


/**
 * @brief   openCode agent management info
 */
typedef struct openCode_agent_management_information
{
    /// 에이전트 버전 정보
    mild_u32                    agent_version;

    /// 에이전트 실행 PID
    mild_i32                    agent_pid;

    /// 에이전트 실행 UID
    mild_i32                    agent_uid;

    /// 에이전트 실행 경로
    mild_i8                     agent_path[ STRLEN_256 ];

    /// 단일 인스턴스를 위한 파일 디스크립터
    mild_i32                    single_fd;

    /// netlink 소켓 디스크립터
    mild_i32                    netlink_fd;

    /// 로그 파일 디스크립터
    mild_i32                    log_fd;

    /// 스레드 핸들 및 상태 정보
    OPENCODE_CONTROL            control;

    /// 라이브러리 핸들 및 버전 정보
    OPENCODE_LIBRARY_HANDLE     library;

    /// sysfs 획득 정보
    OPENCODE_SYSFS_INFO         sysfs;

    /// 로컬 시스템 기본 정보
    OPENCODE_SYSTEM_INFO        system;

    /// UI 위젯 정보
    OPENCODE_UI                 ui;

    /// 사용자 정보
    OPENCODE_USER               user;

} OPENCODE_AGENT, *POPENCODE_AGENT;


/// 관리 구조체 외부 참조 선언
extern POPENCODE_AGENT g_agent;


#endif  // #ifndef __AGENT_TYPES_H__
