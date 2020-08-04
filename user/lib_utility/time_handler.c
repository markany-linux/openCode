#include "time_handler.h"

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "utility_interface.h"


/**
 * @brief   반환 버퍼에 msec, usec 값을 붙이는 함수
 *          msec, usec 각 2자리씩 획득하여 mmuu 순서 및 형태로 버퍼에 붙임
 * 
 * @param   stamp__ 타임 스템프 반환 버퍼
 */
static void attach_mm_nn(
    mild_str                    stamp__
    )
{
    struct timeval tv;
	mild_i64 msec = 0;
    mild_i8 buf[ STRLEN_16 ] = { 0, };

    /// 시간 정보 획득
	gettimeofday( &tv, NULL );

    /// msec 계산
	msec = ( tv.tv_sec * 1000LL ) + ( tv.tv_usec / 1000 );

    /// msec 정보를 버퍼에 2자리 추가 후, 스템프에 추가
    sprintf( buf, "%lld", msec );
    memcpy( stamp__, buf + ( strlen( buf ) - 2 ), 2 );

    /// usec 정보를 버퍼에 2자리 추가 후, 스템프에 붙임
    sprintf( buf, "%ld", tv.tv_usec );
    memcpy( stamp__ + strlen( stamp__ ), buf, 2 );
}


mild_bool get_current_timestamp(
    mild_str                    stamp__
    )
{
    time_t tmp;
    struct tm *tinfo = mild_null;

    NULL_PTR_RETURN( stamp__ );

    /// 현재 시간 획득
    if( -1 == time( &tmp ) )
        return mild_false;

    /// 시간 변환
    tinfo = localtime( &tmp );

    /// 년월일시분초 시간 정보 생성 후 버퍼에 기록
    sprintf( stamp__, "%d%02d%02d%02d%02d%02d",
			tinfo->tm_year + 1900, tinfo->tm_mon + 1, tinfo->tm_mday,
			tinfo->tm_hour, tinfo->tm_min, tinfo->tm_sec );

    return mild_true;
}

mild_bool getCurrentTimestamp(
    mild_str                    stamp__
    )
{
	return get_current_timestamp( stamp__ );
}


mild_bool get_current_timestamp_mn(
	mild_str					stamp__
	)
{
    NULL_PTR_RETURN( stamp__ );

    /// 년월일시분초 형태의 타임 스템프 획득
    if( mild_false == get_current_timestamp( stamp__ ) )
        return mild_false;

    /// 타임 스템프에 msec, usec 추가
    attach_mm_nn( stamp__ + strlen( stamp__ ) );

    return mild_true;
}

mild_bool getCurrentTimestampMn(
	mild_str					stamp__
	)
{
	return get_current_timestamp_mn( stamp__ );
}


mild_bool get_current_time(
	mild_u64					*time__
	)
{
	time_t tmp;

	NULL_PTR_RETURN( time__ );

	/// 현재 시간 획득
	if( -1 == time( &tmp ) )
		return mild_false;

	/// 획득 시간을 반환
	*time__ = tmp;

	return mild_true;
}

mild_bool getCurrentTime(
	mild_u64					*time__
	)
{
	return get_current_time( time__ );
}


void get_time_readable(
	mild_u64					time__,
	mild_str					buf__
	)
{
	time_t time = time__;
	struct tm *info = mild_null;

	NULL_PTR_VOID( buf__ );

	/// 전달 시간이 0인지 확인
	if( 0 == time__ )
	{
		/// 0인 경우, 0으로 시간을 설정하고 반환
		sprintf( buf__, "00.00.00" );
		return;
	}

	/// 시간을 읽을 수 있도록 변환하여 반환
	info = localtime( &time );
	sprintf( buf__, "%02d.%02d.%02d",
		info->tm_hour, info->tm_min, info->tm_sec );
}

void getTimeReadable(
	mild_u64					time__,
	mild_str					buf__
	)
{
	return get_time_readable( time__, buf__ );
}


void get_date_readable(
	mild_u64					time__,
	mild_str					buf__
	)
{
	time_t time = time__;
	struct tm *info = mild_null;

	NULL_PTR_VOID( buf__ );

	/// 전달 시간이 0인지 확인	
	if( 0 == time__ )
	{
		/// 0인 경우, 0으로 날짜를 설정하고 반환
		sprintf( buf__, "0000.00.00" );
		return;
	}

	/// 날짜를 읽을 수 있도록 변환하여 반환
	info = localtime( &time );
	sprintf( buf__, "%d.%02d.%02d",
		info->tm_year + 1900, info->tm_mon + 1, info->tm_mday );
}

void getDateReadable(
	mild_u64					time__,
	mild_str					buf__
	)
{
	return get_date_readable( time__, buf__ );
}


/**
 * @brief	전달된 버퍼를 인수에 맞도록 0으로 설정하여 반환
 * 
 * @param	buf__	반환할 버퍼
 * @param	date__	날짜 초기화 여부
 * @param	time__	시간 초기화 여부
 */
static void set_time_zero(
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	)
{
	NULL_PTR_VOID( buf__ );

	/// 시간과 날짜 초기화 여부에 따라 초기화 수행
	if( date__ & time__ )
		sprintf( buf__, "0000.00.00-00.00.00" );
	else if( mild_false != date__ )
		sprintf( buf__, "0000.00.00" );
	else if( mild_false != time__ )
		sprintf( buf__, "00.00.00" );
	else
		sprintf( buf__, "0000.00.00-00.00.00" );
}


void get_date_time_readable(
	mild_u64					current__,
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	)
{
	time_t time = current__;
	struct tm *info = mild_null;

	NULL_PTR_VOID( buf__ );

	/// 시간 정보가 없다면 0으로 초기화하여 반환
	if( 0 == current__ )
		return set_time_zero( buf__, date__, time__ );

	/// 현재 시간 정보를 획득
	info = localtime( &time );

	/// 인수에 따라 날짜/시간 정보를 입력하여 반환
	if( date__ & time__ )
	{
		sprintf( buf__, "%d.%02d.%02d-%02d.%02d.%02d",
			info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
			info->tm_hour, info->tm_min, info->tm_sec );
	}
	else if( mild_false != date__ )
	{
		sprintf( buf__, "%d.%02d.%02d",
			info->tm_year + 1900, info->tm_mon + 1, info->tm_mday );
	}
	else if( mild_false != time__ )
	{
		sprintf( buf__, "%02d.%02d.%02d",
			info->tm_hour, info->tm_min, info->tm_sec );
	}
	else
	{
		sprintf( buf__, "0000.00.00-00.00.00" );
	}
}

void getDateTimeReadable(
	mild_u64					current__,
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	)
{
	return get_date_time_readable( current__, buf__, date__, time__ );
}


/**
 * @brief	시간 정보 처리를 위한 공용 함수
 * 
 * @param	buf__	반환할 버퍼
 * @param	date__	날짜 변환 여부
 * @param	time__	시간 변환 여부
 * 
 * @return	시간 획득 및 반환 성공 true, 실패 false
 */
static mild_bool common_time_handler(
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	)
{
	mild_u64 ctime = 0;

	NULL_PTR_RETURN( buf__ );

	/// 1. 현재 시간 획득	
	if( mild_false == get_current_time( &ctime ) )
	{
		printf( "Fail to get current time\n" );
		return mild_false;
	}

	/// 2. 날짜/시간 정보를 읽을 수 있도록 변환
	get_date_time_readable( ctime, buf__, date__, time__ );

	return mild_true;
}


mild_bool get_current_time_readable(
	mild_str					buf__
	)
{
	return common_time_handler( buf__, mild_false, mild_true );
}

mild_bool getCurrentTimeReadable(
	mild_str					buf__
	)
{
	return common_time_handler( buf__, mild_false, mild_true );
}


mild_bool get_current_date_readable(
	mild_str					buf__
	)
{
	return common_time_handler( buf__, mild_true, mild_false );
}

mild_bool getCurrentDateReadable(
	mild_str					buf__
	)
{
	return common_time_handler( buf__, mild_true, mild_false );
}


mild_bool get_current_date_time_readable(
	mild_str					buf__
	)
{
	return common_time_handler( buf__, mild_true, mild_true );
}

mild_bool getCurrentDateTimeReadable(
	mild_str					buf__
	)
{
	return common_time_handler( buf__, mild_true, mild_true );
}


void dispTimeReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	)
{
	struct tm *time = localtime( ( time_t* )&time__ );

	printf( "%02d.%02d.%02d",
		time->tm_hour, time->tm_min, time->tm_sec );

	if( linefeed__ )
		printf( "\n" );
}


void dispDateReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	)
{
	struct tm *time = localtime( ( time_t* )&time__ );

	printf( "%d.%02d.%02d",
		time->tm_year + 1900, time->tm_mon + 1, time->tm_mday );

	if( linefeed__ )
		printf( "\n" );
}


void dispDateTimeReadable(
	mild_u64					time__
	)
{
	dispDateReadable( time__, mild_false );
	printf( "-" );
	dispTimeReadable( time__, mild_true );
}


/**
 * @brief	코드 동작 시간 정보 처리를 위한 정보 구조체
 */
typedef struct app_execution_time_check_info
{
	/// 코드 동작 시간 측정을 위한 시작 시간
	clock_t						app_start;

	/// 코드 동작 시간 측정을 위한 종료 시간
	clock_t						app_end;

	/// 시작 시간 설정 여부
	mild_bool					set_app;

} APP_TIME, *PAPP_TIME;


/// * 응용 프로그램 동작 시간 획득을 위한 전역 변수
static APP_TIME g_app_time;


void set_app_start_time( void )
{
	/// 시간 측정 시작 시간 설정 정보
	g_app_time.set_app = mild_true;

	/// 현재 시간을 획득
	g_app_time.app_start = clock( );
}

void setAppStartTime( void )
{
	return set_app_start_time( );
}


mild_float set_app_end_time( void )
{
	mild_float result = 0;

	/// 시작 시간이 설정되어 있는지 여부 확인
	if( mild_false == g_app_time.set_app )
	{
		printf( "Application start time is not setup yet\n" );
		return ( mild_float )0;
	}

	/// 종료 시간 획득
	g_app_time.app_end = clock( );

	/// 시작, 종료 시간을 이용하여 동작 시간 획득
	result = ( mild_float )( g_app_time.app_end - g_app_time.app_start )/CLOCKS_PER_SEC;

	/// 종료 시간 획득으로 초기화를 설정
	g_app_time.set_app = mild_false;

	return result;
}

mild_float setAppEndTime( void )
{
	return set_app_end_time( );
}


/**
 * @brief	시간 차이 출력 함수
 * 
 * @param	label__	출력할 라벨. NULL 허용
 * @param	ti__	시간 정보 구조체
 */
static void dprint_time_interval(
	mild_cstr					label__,
	PTIME_INTERVAL				ti__
	)
{
	mild_float result = 0.0;

	/// 시작, 종료 시간을 이용하여 동작 시간 획득
	result = ( mild_float )( g_app_time.app_end - g_app_time.app_start )/CLOCKS_PER_SEC;

	/// 라벨 존재 시, 출력
	if( mild_null != label__ )
		printf( "%s ", label__ );

	printf( "time interval: %f\n", result );
}


void setTimeInterval(
	mild_cstr					label__,
	PTIME_INTERVAL				ti__,
	mild_bool					start__
	)
{
	mild_long time = 0;

	/// 시간 값을 먼저 획득
	time = clock( );

	if( mild_null == ti__ )
		return;

	/// 측정 시작 여부 확인
	if( mild_false != start__ )
	{
		/// 시작이면 획득 시간을 설정하고 반환
		ti__->start = time;
		return;
	}

	/// 종료 시간 설정
	ti__->end = time;

	/// 시간 차이 출력 함수 호출
	return dprint_time_interval( label__, ti__ );
}
