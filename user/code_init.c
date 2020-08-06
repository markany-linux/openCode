#include "code_init.h"

#include <string.h>
#include <unistd.h>

#include "code_definitions.h"
#include "code_helper.h"
#include "code_version.h"
#include "utility_interface.h"


/**
 * @brief   대부분 실패하지 않는 기본 정보 획득 및 설정
 * 
 * @param   agent__ 정보 구조체
 */
static void set_opencode_default_values(
    POPENCODE_AGENT             agent__
    )
{
    /// Process ID
    agent__->agent_pid = getpid( );

    /// User ID
    agent__->agent_uid = getuid( );

    /// openCode agent version
    agent__->agent_version = OPENCODE_VERSION;

    /// get current working directory. 실패 시 임시 디렉터리로 설정
    if( mild_null == getcwd( agent__->agent_path, STRLEN_128 ) )
        memcpy( agent__->agent_path, OPENCODE_TMP_DIR, strlen( OPENCODE_TMP_DIR ) );

}


mild_bool init_opencode_agent(
    POPENCODE_AGENT             *agent__
    )
{
    POPENCODE_AGENT agent = mild_null;

    /// 에이전트 메모리 할당
    if( mild_false == malloc_code_agent( agent__ ) )
        return mild_false;

    agent = *agent__;

    set_opencode_default_values( agent );

    /// 사용자 정보 설정
    if( mild_false == set_user_info( agent->agent_uid, &( agent->user ) ) )
        return mild_false;

    /// FIXME: merge 후, 추가 초기화 수행

    return mild_true;
}


void cleanup_opencode_agent(
    POPENCODE_AGENT             agent__
    )
{

    /// 가장 마지막에 에이전트 메모리 해제
    free_code_agent( agent__ );
}
