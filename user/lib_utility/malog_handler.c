#include "malog_handler.h"

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "file_check.h"
#include "time_handler.h"
#include "dprint.h"
#include "event_messages.h"
#include "utility_interface.h"


/// 로그 파일 디스크립터
mild_i32 g_malog_fd;


/**
 * @brief   로그 기록 디렉터리 관련 처리를 수행
 *          * 디렉터리 기본 위치: 에이전트 실행 위치 하위의 "logs" 디렉터리
 * 
 * @param   path__  에이전트 설치 경로
 * 
 * @return  디렉터리 접근에 문제 없음 true, 문제 있음 false
 */
static mild_bool setup_malog_dir(
    mild_cstr                   path__
    )
{
    mild_i32 mode = S_IRUSR | S_IWUSR | S_IRGRP;
    mild_i8 buf[ STRLEN_128 ] = { 0, };

    /// 1. 에이전트 설치 경로 존재 여부 확인
    if( mild_null == path__ )
    {
        //dprint_error( INIT_SET_AGENT_PATH_FAIL );
        return mild_false;
    }

    /// 2. 에이전트 설치 경로에 대한 권한 존재 여부 확인
    if( mild_false == check_access_rdwr( path__ ) )
    {
        dprint_error( DRM_ERROR_LOG_DIRECTORY_ACCESS );
        return mild_false;
    }

    /// 3. 로그 디렉터리 문자열 생성
    sprintf( buf, "%s/logs", path__ );

    /// 4. 대상 디렉터리가 존재하는지 여부 확인
    if( mild_false == check_directory_filetype( buf ) )
    {
        /// 4-1F. 로그 기록 디렉터리 생성. 실패 시 반환
        if( -1 == mkdir( buf, mode ) )
        {
            dprint_error( DRM_ERROR_LOG_DIRECTORY_CREATE );
            return mild_false;
        }
    }

    /// 2. 읽기 쓰기 권한이 존재하는지 여부 확인. 권한이 없으면 반환
    if( mild_false == check_access_rdwr( buf ) )
    {
        dprint_error( DRM_ERROR_LOG_DIRECTORY_ACCESS );
        return mild_false;
    }

    return mild_true;
}


mild_bool init_malog(
    mild_cstr                   path__
    )
{
	mild_i32 mode = S_IRUSR | S_IWUSR | S_IRGRP;
	mild_i8 cur_date[ STRLEN_24 ] = { 0, };
	mild_i8 log_name[ STRLEN_256 ] = { 0, };

    NULL_PTR_RETURN( path__ );

    /// 1. 로그 파일이 개방 상태인지 확인
    if( FD_START <= g_malog_fd )
        return mild_true;

    /// 2. 오늘 날짜 획득
	if( mild_false == get_current_date_readable( cur_date ) )
        return mild_false;

    /// 3. 로그 디렉터리 확인
    setup_malog_dir( path__ );

    /// 4. 로그 파일 이름 생성
    sprintf( log_name, "%s/logs/malog_%s.log", path__, cur_date );

    /// 5. 대상 파일 존재 여부 확인
    if( mild_false == check_file_exist( log_name ) )
    {
        /// 5-1F. 로그 파일 생성
        g_malog_fd = open( log_name, O_CREAT | O_RDWR | O_TRUNC, mode );
        if( FD_START > g_malog_fd )
        {
            dprint_error( DRM_ERROR_LOG_FILE_CREATE );
            return mild_false;
        }
    }
    else
    {
        /// 5-2T. 로그 파일 개방
        g_malog_fd = open( log_name, O_RDWR, mode );
        if( FD_START > g_malog_fd )
        {
            dprint_error( DRM_ERROR_LOG_FILE_OPEN );
            return mild_false;
        }
    }

    /// 6. 로그 파일의 마지막 위치로 파일 포인터 이동
	if( -1 == lseek( g_malog_fd, 0, SEEK_END ) )
	{
		dprint( _CM_, "Log file[ %s ] lseek fail", log_name );
		cleanup_malog( );
		return mild_false;
	}

	return mild_true;
}

mild_bool initMalogFile(
    mild_cstr                   pathname__
    )
{
    return init_malog( pathname__ );
}


mild_bool malog_dprint_write(
    mild_cstr                   msg__
    )
{
    INVALID_FD_RETURN( g_malog_fd );

    if( 0 > write( g_malog_fd, msg__, strlen( msg__ ) ) )
    {
        dprint_error( DRM_ERROR_LOG_FILE_WRITE );
        return mild_false;
    }

    return mild_true;
}

mild_bool malogDprintWrite(
    mild_cstr                   msg__
    )
{
    return malog_dprint_write( msg__ );
}


void cleanup_malog( void )
{
    INVALID_FD_VOID( g_malog_fd );

    dprint( _IM_, "Log file descriptor cleanup" );
    dprintMessages( mild_true, "///// Agent cleanup sequence finish /////" );

    close( g_malog_fd );
    g_malog_fd = 0;
}


void cleanupMalogFile( void )
{
    return cleanup_malog( );
}
