#include "single_instance.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


/// 기능 자체적으로 파일 디스크립터를 관리하기 위해 선언
static mild_i32 g_lockfd;


mild_bool setup_single_instance(
    mild_cstr                   pathname__
    )
{
    mild_i8 buf[ STRLEN_8 ] = { 0, };
    struct flock fl;

    NULL_PTR_RETURN( pathname__ );

    /// 1. 이미 파일이 열려 있다면 즉시 참 반환
    if( FD_START < g_lockfd )
        return mild_true;

    /// 2. 현재 PID 값을 획득
    sprintf( buf, "%d", getpid( ) );

    /// 3. 파일 잠금 설정. 파일 시작부터 기록할 길이만큼 기록 금지로 설정
    fl.l_type = F_WRLCK;        //> 잠금 타입
    fl.l_whence = SEEK_SET;     //> 잠금 위치
    fl.l_start = 0;             //> 잠금 위치 부터 변위
    fl.l_len = strlen( buf );   //> 잠금 길이

    /// 4. 잠금 파일 생성
    g_lockfd = open( pathname__, O_CREAT | O_RDWR, 0666 );
    INVALID_FD_RETURN( g_lockfd );

    do
    {
        /// 5. 잠금 설정을 생성한 파일에 적용
        if( 0 > fcntl( g_lockfd, F_SETLK, &fl  ) )
            break;

        /// 6. 잠금 파일에 에이전트의 PID 기록
        if( 0 > write( g_lockfd, buf, strlen( buf ) ) )
            break;

        /// 7. 성공 반환
        return mild_true;

    } while( mild_false );

    /// 8. 잠금 설정 실패나 기록 실패 시 파일 해제
    cleanup_single_instance( pathname__ );

    /// 9. 실패 반환
    return mild_false;
}


mild_bool setupSingleInstance(
    mild_cstr                   pathname__
    )
{
    return setup_single_instance( pathname__ );
}


void cleanup_single_instance(
    mild_cstr                   pathname__
    )
{
    NULL_PTR_VOID( pathname__ );

    /// 1. 파일이 생성된 적이 없다면 처리하지 않음
    INVALID_FD_VOID( g_lockfd );

    /// 2. 파일 디스크립터를 닫고 초기화
    close( g_lockfd );
    g_lockfd = 0;

    /// 3. 대상 파일을 삭제
    unlink( pathname__ );
}


void cleanupSingleInstance(
    mild_cstr                   pathname__
    )
{
    return cleanup_single_instance( pathname__ );
}
