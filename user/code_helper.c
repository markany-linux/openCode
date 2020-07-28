#include "code_helper.h"

#include <sys/types.h>
#include <pwd.h>


mild_bool malloc_code_agent(
    POPENCODE_AGENT             *agent__
    )
{
    POPENCODE_AGENT agent = mild_null;

    /// 메모리 할당 및 확인
    agent = ( POPENCODE_AGENT )malloc( sizeof( OPENCODE_AGENT ) );
    if( mild_null == agent )
    {
        printf( "openCode memory allocation fail for agent\n" );
        return mild_false;
    }

    /// 초기화
    memset( agent, 0x00, sizeof( OPENCODE_AGENT ) );

    *agent__ = agent;

    return mild_true;
}


void free_code_agent(
    POPENCODE_AGENT             agent__
    )
{
    if( mild_null == agent__ )
        return;

    /// 정보 초기화
    memset( agent__, 0x00, sizeof( OPENCODE_AGENT ) );

    free( agent__ );
}


mild_bool set_user_info(
    mild_i32                    pid__,
    POPENCODE_USER              user__
    )
{
    struct passwd *pwd = mild_null;

    if( mild_null == user__ )
    {
        printf( "NULL pointer received\n" );
        return mild_false;
    }

    /// 사용자의 정보 획득
    pwd = getpwuid( pid__ );

    /// 사용자 아이디, 이름, 홈 디렉터리를 데이터에 기록
    user__->user_id = pwd->pw_uid;
    memcpy( user__->user_name, pwd->pw_name, strlen( pwd->pw_name ) );
    memcpy( user__->user_home, pwd->pw_dir, strlen( pwd->pw_dir ) );

    return mild_true;
}
