#include "code_init.h"

#include <unistd.h>

#include "code_helper.h"
#include "utility_interface.h"



mild_bool init_opencode_agent(
    POPENCODE_AGENT             *agent__
    )
{
    POPENCODE_AGENT agent = mild_null;

    /// 에이전트 메모리 할당
    if( mild_false == malloc_code_agent( agent__ ) )
        return mild_false;

    agent = *agent__;

    /// 에이전트 PID
    agent->agent_pid = getpid( );

    /// 사용자 정보 설정
    if( mild_false == set_user_info( agent->agnet_pid, &( agent->user ) ) )
        return mild_false;

    /// FIXME: merge 후, 추가 초기화 수행

    return mild_true;
}


void cleanup_opencode_agent(
    POPENCODE_AGENT             agent__
    )
{

    /// 가장 마지막에 에이전트 메모리 해제
    free_opencode_agent( agent__ );
}
