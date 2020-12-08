#include "code_init.h"

#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

#include "code_definitions.h"
#include "code_helper.h"
#include "code_version.h"
#include "code_gui_init.h"
#include "utility_interface.h"


/**
 * @brief   대부분 실패하지 않는 기본 정보 획득 및 설정
 * 
 * @param   agent__ 정보 구조체
 */
static mild_bool init_opencode_execute_environment(
    POPENCODE_AGENT             agent__
    )
{
    mild_i8 buf[ STRLEN_512 ] = { 0, };

    /// openCode agent version
    agent__->agent_version = OPENCODE_VERSION;

    /// Process ID
    agent__->agent_pid = getpid( );

    /// User ID
    agent__->agent_uid = getuid( );

    /// 작업 디렉터리 획득. 실패 시 임시 디렉터리로 설정
    if( mild_null == getcwd( agent__->agent_path, STRLEN_256 ) )
        memcpy( agent__->agent_path, OPENCODE_TMP_DIR, strlen( OPENCODE_TMP_DIR ) );

    /// 로컬 시스템 정보 획득
    if( mild_false == getLocalSystemInfo( &agent__->system ) )
        return mild_false;

    /// 설정 정보 획득을 위한 기본 정보 생성
    if( mild_false == createConfigList( &agent__->library.config_handle ) )
    {
        printf( "create config list\n" );
        return mild_false;
    }

    /// 설정 정보를 획득할 경로 생성. 설정 정보는 현재 작업 디렉터리에 존재한다고 가정
    snprintf( buf, STRLEN_512, "%s/%s", agent__->agent_path, OPENCODE_CONFIG_FILE );

    /// 생성 경로에서 설정 파일을 읽어 들여 초기화
    if( mild_false == initConfigList( agent__->library.config_handle, buf ) )
    {
        printf( "Fail to get config file\n" );
        return mild_false;
    }

    return mild_true;
}


/**
 * @brief   라이브러리 로딩
 * 
 * @return  로딩 성공 true, 실패 false
 */
static mild_bool load_library( void )
{
    /// 유틸리티 라이브러리 개방 및 확인
    g_agent->library.lib_utility = dlopen( "libopencode.so", RTLD_NOW );
    if( mild_null == g_agent->library.lib_utility )
    {
        printf( "Fail to load library\n" );
        return mild_false;
    }

    return mild_true;
}


mild_bool init_opencode_agent(
    POPENCODE_AGENT             *agent__
    )
{
    POPENCODE_AGENT agent = mild_null;

    /// 에이전트 설정 정보 전역 보관을 위한 메모리 할당
    if( mild_false == malloc_code_agent( &agent ) )
        return mild_false;

    /// 획득 메모리 설정
    *agent__ = agent;

    /// 유틸리티 라이브러리 로딩
    if( mild_false == load_library( ) )
        return mild_false;

    /// 단일 인스턴스 생성 처리
    if( mild_false == setupSingleInstance( &agent->single_fd, SINGLE_INSTANCE_NAME ) )
        return mild_false;

    /// 에이전트 동작 기본 정보 설정
    init_opencode_execute_environment( agent );

    /// 사용자 정보 획득
    if( mild_false == set_user_info( agent->agent_uid, &( agent->user ) ) )
        return mild_false;

    return mild_true;
}


void cleanup_opencode_agent( void )
{
    /// 에이전트 동적 생성 메모리 해제
    free_code_agent( g_agent );
}
