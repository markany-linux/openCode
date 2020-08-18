#include "single_instance.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "file_check.h"


/// 기능 자체적으로 파일 디스크립터를 관리하기 위해 선언
static mild_i32 g_lockfd;


mild_bool setup_single_instance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    )
{
    mild_i8 buf[ STRLEN_8 ] = { 0, };
    struct flock fl;

    /// 잠금 파일 생성 버퍼 확인
    if( mild_null == pathname__ )
        return mild_false;

    /// 파일이 열려 있는 디스크립터라면 처리하지 않음
    if( FD_START < *fd__ )
        return mild_true;

    /// 생성할 디렉터리 경로 존재 여부 확인
    if( mild_false == check_directory_exist( pathname__ ) )
    {
        printf( "Request pathname is not exist\n" );
        return mild_false;
    }

    /// 디렉터리 접근 권한 존재 여부 확인
    if( mild_false == check_access_read_write( pathname__ ) )
    {
        printf( "Not enough permission to request pathname\n" );
        return mild_false;
    }

    /// PID 값으로 기록할 내용 생성
    sprintf( buf, "%d", getpid( ) );

    /// 파일 잠금 설정. 파일 시작부터 기록할 길이만큼 기록 금지로 설정
    fl.l_type = F_WRLCK;        // 잠금 타입
    fl.l_whence = SEEK_SET;     // 잠금 위치
    fl.l_start = 0;             // 잠금 위치 부터 변위
    fl.l_len = strlen( buf );   // 잠금 길이

    /// 잠금 파일 생성 및 확인
    *fd__ = open( pathname__, O_CREAT | O_RDWR, 0666 );
    if( FD_START > *fd__ )
    {
        printf( "Fail to create lock file" );
        return mild_false;
    }

    do
    {
        /// 잠금 설정을 생성한 파일에 적용
        if( 0 > fcntl( *fd__, F_SETLK, &fl  ) )
            break;

        /// 잠금 파일에 에이전트의 PID 기록
        if( 0 > write( *fd__, buf, strlen( buf ) ) )
            break;

        return mild_true;

    } while( mild_false );

    /// 8. 잠금 설정 실패나 기록 실패 시 파일 해제
    cleanup_single_instance( fd__, pathname__ );

    /// 9. 실패 반환
    return mild_false;
}


mild_bool setupSingleInstance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    )
{
    /// 디스크립터가 전달되지 않으면, 자체 전역 변수 이용
    if( mild_null == fd__ )
        return setup_single_instance( &g_lockfd, pathname__ );

    return setup_single_instance( fd__, pathname__ );
}


void cleanup_single_instance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    )
{
    /// 경로 전달 확인
    if( mild_null == pathname__ )
        return;

    /// 파일 디스크립터 확인
    if( FD_START > *fd__ )
        return;

    /// 파일 디스크립터를 닫고 초기화
    close( *fd__ );
    *fd__ = 0;

    /// 대상 파일을 삭제
    if( -1 == unlink( pathname__ ) )
    {
        printf( "Fail to delete requst file\n" );
    }
}


void cleanupSingleInstance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    )
{
    /// 디스크립터가 전달되지 않으면, 자체 전역 변수 이용
    if( mild_null == fd__ )
        return cleanup_single_instance( &g_lockfd, pathname__ );

    return cleanup_single_instance( fd__, pathname__ );
}
