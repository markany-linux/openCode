#include "code_init.h"

#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

#include "code_definitions.h"
#include "code_helper.h"
#include "code_version.h"
//#include "utility_interface.h"
#include "code_gui_init.h"


/**
 * @brief   대부분 실패하지 않는 기본 정보 획득 및 설정
 * 
 * @param   agent__ 정보 구조체
 */
static mild_bool init_opencode_execute_environment(
    POPENCODE_AGENT             agent__
    )
{
    /// openCode agent version
    agent__->agent_version = OPENCODE_VERSION;

    /// Process ID
    agent__->agent_pid = getpid( );

    /// User ID
    agent__->agent_uid = getuid( );

    /// get current working directory. 실패 시 임시 디렉터리로 설정
    if( mild_null == getcwd( agent__->agent_path, STRLEN_128 ) )
        memcpy( agent__->agent_path, OPENCODE_TMP_DIR, strlen( OPENCODE_TMP_DIR ) );

    /// TODO: 시스템 정보 획득
    if( mild_false == getLocalSystemInfo( &agent__->system ) )
        return mild_false;


printf( "%s 1\n", __FUNCTION__ );

    if( mild_false == createConfigList( &agent__->library.config_handle ) )
    {
        printf( "create config list\n" );
        return mild_false;
    }

    if( mild_false == initConfigList( agent__->library.config_handle, "/home/work/openCode/bin/config.cfg" ) )
    {
        printf( "Fail to get config file\n" );
        return mild_false;
    }

printf( "%s 2\n", __FUNCTION__ );
    /// TODO: 로그 초기화 - 나중에

    /// TODO: 환경 설정 정보 초기화

    return mild_true;
}

static mild_bool check_kernel_module_online(
    void
    )
{
    /// TODO: 커널 모듈 적재 여부 확인

    /// TODO: 커널 모듈의 주요 인터페이스 생성 확인

    return mild_true;
}


static mild_bool load_library( void )
{
    g_agent->library.lib_utility = dlopen( "libmautil.so", RTLD_NOW );
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

    /// agent memory allocation
    if( mild_false == malloc_code_agent( &agent ) )
        return mild_false;

    *agent__ = agent;

    if( mild_false == load_library( ) )
        return mild_false;

    /// TODO: single instance
    if( mild_false == setupSingleInstance( &agent->fd, SINGLE_INSTANCE_NAME ) )
        return mild_false;

    /// 기본 정보 설정
    init_opencode_execute_environment( agent );

    /// 사용자 정보 설정
    if( mild_false == set_user_info( agent->agent_uid, &( agent->user ) ) )
        return mild_false;


    return mild_true;
}


void cleanup_opencode_agent( void )
{

    /// 가장 마지막에 에이전트 메모리 해제
    free_code_agent( g_agent );
}
