#include "common.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "code_init.h"


/// agent management info.
POPENCODE_AGENT g_agent;


int main(
    int                         argc__,
    char                        **argv__
    )
{
    printf( "Hello openCode\n" );

    /// openCode 초기화
    if( mild_false == init_opencode_agent( &g_agent ) )
    {
        printf( "openCode initialize fail\n" );
        return -1;
    }



    /// openCode 종료
    cleanup_opencode_agent( g_agent );

    return 0;
}
