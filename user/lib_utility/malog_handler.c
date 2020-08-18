#include "malog_handler.h"

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "file_check.h"
#include "time_handler.h"
#include "interface/lib_utility.h"




/**
 * @brief   로그 기록 디렉터리 관련 처리를 수행
 *          * 디렉터리 기본 위치: 전달 경로 하위의 "logs" 디렉터리
 * 
 * @param   path__  로그 파일 기록 위치
 * 
 * @return  디렉터리 접근에 문제 없음 true, 권한 부재/생성 실패 등 false
 */
static mild_bool setup_malog_dir(
    mild_cstr                   pathname__,
    mild_cstr                   dir_name__
    )
{
    mild_i32 mode = S_IRUSR | S_IWUSR | S_IRGRP;
    mild_str dir_name = mild_null;

    /// 1. 전달 경로에 대한 권한 존재 여부 확인
    if( mild_false == check_access_read_write( pathname__ ) )
    {
        printf( "%s directory access permission not exist\n", pathname__ );
        return mild_false;
    }

    /// 2. 생성할 디렉터리 경로 메모리 할당 및 확인
    dir_name = ( mild_str )malloc( strlen( pathname__ ) + STRLEN_8 );
    if( mild_null == dir_name )
    {
        printf( "Memory allocation fail for directory name\n" );
        return mild_false;
    }

    /// 3. 로그 디렉터리 문자열 생성
    if( mild_null == dir_name__ )
    {
        snprintf( dir_name, strlen( pathname__ ) + STRLEN_8, "%s/%s", pathname__, DEFAULT_LOG_DIR_NAME );
    }
    else
    {
        snprintf( dir_name, strlen( pathname__ ) + STRLEN_8, "%s/%s", pathname__, dir_name__ );
    }

    /// 4. 대상 디렉터리가 존재하는지 여부 확인
    if( mild_false == check_directory_filetype( dir_name ) )
    {
        /// 1F. 존재하지 않을 경우 로그 기록 디렉터리 생성
        if( -1 == mkdir( dir_name, mode ) )
        {
            printf( "Fail to create log directory\n" );
            return mild_false;
        }
    }

    /// 5. 읽기 쓰기 권한이 존재하는지 여부 확인. 권한이 없으면 반환
    if( mild_false == check_access_read_write( dir_name ) )
    {
        printf( "Directory access permission not exist\n" );
        return mild_false;
    }

    return mild_true;
}


mild_bool init_malog(
    mild_i32                    *fd__,
    mild_cstr                   pathname__,
    mild_cstr                   dir_name__
    )
{
    mild_i32 len = 0;
	mild_i32 mode = S_IRUSR | S_IWUSR | S_IRGRP;
	mild_i8 today[ STRLEN_24 ] = { 0, };
    mild_str log_name = mild_null;

	if( mild_null == fd__ )
		return mild_false;

    /// 로그 파일이 개방 상태인지 확인
    if( FD_START <= *fd__ )
        return mild_true;

    /// 오늘 날짜 획득
	if( mild_false == get_current_date_readable( today ) )
        return mild_false;

    /// 로그 디렉터리 확인
    setup_malog_dir( pathname__, dir_name__ );

    /// 로그 파일 이름 버퍼 생성
    if( mild_null == dir_name__ )
    {
        /// 여유 있게 버퍼 길이 설정
        len = strlen( pathname__ ) + STRLEN_128;
        /// 디렉터리 명을 지정하지 않은 경우
        log_name = ( mild_str )malloc( len );
    }
    else
    {
        /// 버퍼 길이 설정
        len = strlen( pathname__ ) + strlen(dir_name__ ) + STRLEN_64;
        /// 디렉터리 명을 지정한 경우
        log_name = ( mild_str )malloc( len );
    }

    /// 버퍼 생성 확인
    if( mild_null == log_name )
    {
        printf( "Memory allocation fail to create log file name buffer\n" );
        return mild_false;
    }

    /// 로그 파일 이름 생성
    if( mild_null == dir_name__ )
    {
        snprintf( log_name, len, "%s/%s/malog_%s.log", pathname__, DEFAULT_LOG_DIR_NAME, today );
    }
    else
    {
        snprintf( log_name, len, "%s/%s/malog_%s.log", pathname__, dir_name__, today );
    }

    /// 생성된 로그 파일 존재 여부 확인
    if( mild_false == check_file_exist( log_name ) )
    {
        /// 로그 파일 생성 및 확인
        *fd__ = open( log_name, O_CREAT | O_RDWR | O_TRUNC, mode );
        if( FD_START > *fd__ )
        {
            printf( "Fail to create log file: %s\n", log_name );
			free( log_name );
            return mild_false;
        }
    }
    else
    {
        /// 로그 파일 개방 및 확인
        *fd__ = open( log_name, O_RDWR, mode );
        if( FD_START > *fd__ )
        {
            printf( "Fail to open log file: %s\n", log_name );
			free( log_name );
            return mild_false;
        }
    }

    /// 로그 파일의 마지막 위치로 파일 포인터 이동
	if( -1 == lseek( *fd__, 0, SEEK_END ) )
	{
		cleanup_malog( fd__ );
		return mild_false;
	}

	return mild_true;
}

mild_bool initLogFile(
    mild_i32                    *fd__,
    mild_cstr                   pathname__,
    mild_cstr                   dir_name__
    )
{
    if( ( mild_null == pathname__ ) | ( mild_null == fd__ ) )
    {
        printf( "NULL pointer received\n" );
        return mild_false;
    }

    return init_malog( fd__, pathname__, dir_name__ );
}


mild_bool malog_write(
    mild_i32                    fd__,
    mild_cstr                   log__
    )
{
    if( FD_START > fd__ )
    {
        printf( "Invalid file descriptor recevied\n" );
        return mild_false;
    }

    if( mild_null == log__ )
    {
        printf( "NULL log recevied\n" );
        return mild_false;
    }

    if( 0 > write( fd__, log__, strlen( log__ ) ) )
    {
        printf( "Fail to write log\n" );
        return mild_false;
    }

    return mild_true;
}

mild_bool writeLogFile(
    mild_i32                    fd__,
    mild_cstr                   log__
    )
{
    return malog_write( fd__, log__ );
}


void cleanup_malog(
    mild_i32                    *fd__
    )
{
    if( FD_START > *fd__ )
        return;

    close( *fd__ );
    *fd__ = 0;
}

void closeLogFile(
    mild_i32                    *fd__
    )
{
    return cleanup_malog( fd__ );
}
