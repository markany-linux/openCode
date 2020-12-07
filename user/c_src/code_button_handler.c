#include "code_button_handler.h"

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "code_helper.h"
#include "code_init.h"
#include "code_definitions.h"
#include "code_search_dialog.h"


void config_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 buf[ STRLEN_128 ] = { 0, };
    mild_i8 label[ STRLEN_1024 ] = { 0, };
    mild_u32 crc = 0;

    /// 전달된 정보를 위젯으로 변환. 출력 라벨 위젯 획득
    info = ( GtkWidget* )user_data__;

    /// 서버 아이피 설정 정보 획득
    if( mild_false != getConfigListValue( g_agent->library.config_handle, CONFIG_SERVER_IP, buf, STRLEN_128 ) )
    {
        /// 설정 정보 획득 성공 시, CRC 값 계산
        crc = getCRCValue( ( mild_custr )buf, strlen( buf ) );
        /// 전체 출력 버퍼에 획득된 서버 아이피와 CRC 값을 기록
        snprintf( label, STRLEN_1024, "%s = %s [ %X ]\n", CONFIG_SERVER_IP, buf, crc );
    }

    /// 설정 값 획득을 위한 임시 버퍼 초기화
    memset( buf, 0x00, STRLEN_128 );

    /// 포트 설정 정보 획득
    if( mild_false != getConfigListValue( g_agent->library.config_handle, CONFIG_PORT, buf, STRLEN_128 ) )
    {
        /// 포트 번호 획득 성공 시, CRC 값 계산
        crc = getCRCValue( ( mild_custr )buf, strlen( buf ) );
        /// 전체 출력 버퍼에 획득된 포트 번호와 CRC 값을 기록
        snprintf( label + strlen( label ), STRLEN_1024, "%s = %s[ %X ]\n", CONFIG_PORT, buf, crc );
    }

    /// 출력 라벨 위젯에 획득된 정보를 출력
    gtk_label_set_text( GTK_LABEL( info ), label );
}


void system_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 label[ PAGESIZE ] = { 0, };

    /// 출력 라벨 위젯 포인터 획득
    info = ( GtkWidget* )user_data__;

    /// 배포판 아이디가 존재하면, 전체 출력 버퍼에 추가
    if( mild_null != g_agent->system.distrib_id )
        snprintf( label, PAGESIZE, "distrib_id = %s\n", g_agent->system.distrib_id );

    /// 배포판 아이디 LIKE가 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.distrib_id_like )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_id_like = %s\n", g_agent->system.distrib_id_like );

    /// 배포판 명이 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.distrib_name )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_name = %s\n", g_agent->system.distrib_name );

    /// 배포판 버전이 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.distrib_version )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_version = %s\n", g_agent->system.distrib_version );

    /// 배포판 버전 LIKE가 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.distrib_version_id )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_version_id = %s\n", g_agent->system.distrib_version_id );

    /// 배포판 PRETTY NAME이 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.distrib_pretty )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_pretty = %s\n", g_agent->system.distrib_pretty );

    /// 로컬 아이피가 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.local_ip )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "local_ip = %s\n", g_agent->system.local_ip );

    /// 로컬 호스트 이름이 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.local_hostname )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "local_hostname = %s\n", g_agent->system.local_hostname );

    /// NIC가 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.local_nic )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "local_nic = %s\n", g_agent->system.local_nic );

    /// 커널 버전이 존재하면, 출력 버퍼에 추가
    if( mild_null != g_agent->system.kernel_version )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "kernel_version = %s\n", g_agent->system.kernel_version );

    /// 획득된 정보를 위젯에 출력
    gtk_label_set_text( GTK_LABEL( info ), label );
}


void process_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 label[ PAGESIZE ] = { 0, };

    /// 에이전트 버전 정보를 출력 버퍼에 기록
    snprintf( label, TWOPAGE, "Agent Version: %d.%d.%d.%d\n",
        MA_GET_MAJOR_VERSION( g_agent->agent_version ), MA_GET_MINOR_VERSION( g_agent->agent_version ),
        MA_GET_PATCH_VERSION( g_agent->agent_version ), MA_GET_CUSTOM_VERSION( g_agent->agent_version )
    );

    /// 사용자 아이디/이름/홈 디렉터리를 출력 버퍼에 기록
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "USER-ID: %d\n", g_agent->agent_uid );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "USER-NAME: %s\n", g_agent->user.user_name );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "USER-HOME: %s\n", g_agent->user.user_home );

    /// PID/실행파일 경로/단일 인스턴스 실행을 위한 파일 경로를 출력 버퍼에 기록
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "PROCESS-ID: %d\n", g_agent->agent_pid );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "Current Executable Path: %s\n", g_agent->agent_path );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "Single Instance Path: %s\n", SINGLE_INSTANCE_NAME );

    /// 출력 라벨 포인터 획득
    info = ( GtkWidget* )user_data__;

    /// 출력 버퍼를 라벨에 출력
    gtk_label_set_text( GTK_LABEL( info ), label );
}


void proc_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    /// proc 정보 획득 다이얼로그 실행
    search_dialog_run( );
}


void time_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_u64 time = 0;
    mild_i8 buf[ STRLEN_32 ] = { 0, };
    mild_i8 label[ PAGESIZE ] = { 0, };

    /// 출력 라벨 위젯 획득
    info = ( GtkWidget* )user_data__;

    /// 현재 시간을 문자열로 획득하고, 출력 버퍼에 기록
    if( mild_false != getCurrentTimestamp( buf ) )
        snprintf( label, PAGESIZE, "CurrentTimestamp = %s\n", buf );
    /// 임시 버퍼 초기화
    memset( buf, 0x00, STRLEN_32 );

    /// 현재 시간과 msec 시간을 문자열로 획득하고, 출력 버퍼에 기록
    if( mild_false != getCurrentTimestampMn( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentTimestampMn = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    /// 현재 시간을 읽을 수 있는 형태로 획득하고 출력 버퍼에 기록
    if( mild_false != getCurrentTimeReadable( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentTimeReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    /// 현재 날짜를 읽을 수 있는 형태로 획득하고 출력 버퍼에 기록
    if( mild_false != getCurrentDateReadable( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentDateReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    /// 현재 날짜 시간을 읽을 수 있는 형태로 획득하고 출력 버퍼에 기록
    if( mild_false != getCurrentDateTimeReadable( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentDateTimeReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    if( mild_false == getCurrentTime( &time ) )
    {
        printf( "Fail to get current time\n" );
    }

    getTimeReadable( time, buf  );
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "TimeReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    getDateReadable( time, buf );
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "DateReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    getDateTimeReadable( time, buf, mild_true, mild_true );
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "DateTimeReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    gtk_label_set_text( GTK_LABEL( info ), label );
}


void sysfs_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info_label;
    mild_u32 version = 0;
    SYSFS_INFO info = { 0, };
    mild_i8 buf[ STRLEN_64 ] = { 0, };
    mild_i8 label[ STRLEN_1024 ] = { 0, };

    /// 출력 라벨 위젯 획득
    info_label = ( GtkWidget* )user_data__;

    /// sysfs의 버전 파일의 내용을 읽어 들임
    if( mild_false != open_sysfs_get_contents( SYSFS_VERSION_FILE, buf, STRLEN_16 ) )
    {
        /// 획득된 버전 값을 숫자로 변환
        version = atoi( buf );
        /// 버전 매크로를 이용하여 버전 문자열을 출력 버퍼에 기록
        snprintf( label, STRLEN_1024, "openCode Kernel Version: %d.%d.%d.%d\n\n",
            MA_GET_MAJOR_VERSION( version ), MA_GET_MINOR_VERSION( version ),
            MA_GET_PATCH_VERSION( version ), MA_GET_CUSTOM_VERSION( version )
            );
    }
    else
    {
        snprintf( buf, STRLEN_64, "Fail to load \"%s\" file\nCheck Console print message", SYSFS_VERSION_FILE );
        gtk_label_set_text( GTK_LABEL( info_label ), buf );
        return;
    }

    /// sysfs의 정보 제공 구조체를 읽어 들임
    if( mild_false != open_sysfs_get_contents( SYSFS_INFO_FILE, &info, sizeof( SYSFS_INFO ) ) )
    {
        /// 출력 버퍼에 sysfs 버전 정보를 기록
        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "sysfs version : %d.%d.%d.%d\n",
            MA_GET_MAJOR_VERSION( info.sysfs_version ), MA_GET_MINOR_VERSION( info.sysfs_version ),
            MA_GET_PATCH_VERSION( info.sysfs_version ), MA_GET_CUSTOM_VERSION( info.sysfs_version )
            );

        /// 출력 버퍼에 netlink 버전 정보를 기록
        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "netlink version : %d.%d.%d.%d\n",
            MA_GET_MAJOR_VERSION( info.netlink_version ), MA_GET_MINOR_VERSION( info.netlink_version ),
            MA_GET_PATCH_VERSION( info.netlink_version ), MA_GET_CUSTOM_VERSION( info.netlink_version )
            );

        /// 출력 버퍼에 netlink 상태 정보를 기록
        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "Netlink state : %s\n",
            ( mild_false != info.netlink_load ) ? "ONLINE" : "OFFLINE"
            );

        /// 출력 버퍼에 netlink 포트 번호를 기록
        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "Netlink port: %d\n", info.netlink_port );
    }
    else
    {
        snprintf( buf, STRLEN_64, "Fail to load \"%s\" file\nCheck Console print message", SYSFS_INFO_FILE );
        gtk_label_set_text( GTK_LABEL( info_label ), buf );
        return;
    }
    

    /// 출력 버퍼에 획득된 기록이 존재하는지 확인
    if( mild_null == label )
        return;

    /// 출력 라벨에 획득된 정보를 출력
    gtk_label_set_text( GTK_LABEL( info_label ), label );
}


void netlink_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info_label;
    NETLINK_DATA nd = { 0, };
    mild_i8 label[ TWOPAGE ] = { 0, };

    /// 출력 라벨 위젯 획득
    info_label = ( GtkWidget* )user_data__;

    /// netlink 디스크립터 개방 여부 확인
    if( 3 > g_agent->netlink_fd )
    {
        /// 개방되지 않은 경우, netlink를 개방
        if( mild_false == connect_netlink( &g_agent->netlink_fd ) )
        {
            snprintf( label, TWOPAGE, "Fail to connect netlink kernel module\nCheck Console print message" );
            gtk_label_set_text( GTK_LABEL( info_label ), label );
            return;
        }
    }

    do
    {
        /// netlink 데이터 획득 버퍼 구조체 초기화
        memset( &nd, 0x00, sizeof( NETLINK_DATA ) );

        /// netlink 데이터 획득
        if( mild_false == get_netlink_data( g_agent->netlink_fd, &nd ) )
            break;

        /// 전달된 정보가 없는 경우를 확인
        if( 0 == strncmp( NETLINK_NO_LOG_MESSAGE, nd.fname, strlen( nd.fname ) ) )
        {
            /// 전달된 정보가 없음을 출력 버퍼에 기록하고 처리 중단
            snprintf( label, TWOPAGE, "%s", NETLINK_NO_LOG_MESSAGE );
            break;
        }

        /// 획득된 정보를 형식에 맞추어 출력 버퍼에 기록
        snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "PID[ %d ] UID[ %d ] TARGET[ %s ] TASK[ %s ]\n\n",
            nd.pid, nd.uid, nd.fname, nd.task );

    /// netlink 데이터가 더 이상 존재하지 않을 때까지 반복
    } while ( mild_false != nd.remain );

    /// 출력 라벨에 획득 버퍼 출력
    gtk_label_set_text( GTK_LABEL( info_label ), label );
}
