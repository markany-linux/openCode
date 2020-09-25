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

    info = ( GtkWidget* )user_data__;

    if( mild_false != getConfigListValue( g_agent->library.config_handle, CONFIG_SERVER_IP, buf, STRLEN_128 ) )
    {
        crc = getCRCValue( ( mild_custr )buf, strlen( buf ) );
        snprintf( label, STRLEN_1024, "%s = %s [ %X ]\n", CONFIG_SERVER_IP, buf, crc );
    }

    memset( buf, 0x00, STRLEN_128 );

    if( mild_false != getConfigListValue( g_agent->library.config_handle, CONFIG_PORT, buf, STRLEN_128 ) )
    {
        crc = getCRCValue( ( mild_custr )buf, strlen( buf ) );
        snprintf( label + strlen( label ), STRLEN_1024, "%s = %s[ %X ]\n", CONFIG_PORT, buf, crc );
    }

    gtk_label_set_text( GTK_LABEL( info ), label );
}


void system_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 label[ PAGESIZE ] = { 0, };

    info = ( GtkWidget* )user_data__;

    if( mild_null != g_agent->system.distrib_id )
        snprintf( label, PAGESIZE, "distrib_id = %s\n", g_agent->system.distrib_id );

    if( mild_null != g_agent->system.distrib_id_like )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_id_like = %s\n", g_agent->system.distrib_id_like );

    if( mild_null != g_agent->system.distrib_name )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_name = %s\n", g_agent->system.distrib_name );

    if( mild_null != g_agent->system.distrib_version )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_version = %s\n", g_agent->system.distrib_version );

    if( mild_null != g_agent->system.distrib_version_id )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_version_id = %s\n", g_agent->system.distrib_version_id );

    if( mild_null != g_agent->system.distrib_pretty )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "distrib_pretty = %s\n", g_agent->system.distrib_pretty );

    if( mild_null != g_agent->system.local_ip )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "local_ip = %s\n", g_agent->system.local_ip );

    if( mild_null != g_agent->system.local_hostname )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "local_hostname = %s\n", g_agent->system.local_hostname );

    if( mild_null != g_agent->system.local_nic )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "local_nic = %s\n", g_agent->system.local_nic );

    if( mild_null != g_agent->system.kernel_version )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "kernel_version = %s\n", g_agent->system.kernel_version );

    gtk_label_set_text( GTK_LABEL( info ), label );
}


void process_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 label[ PAGESIZE ] = { 0, };

    snprintf( label, TWOPAGE, "Agent Version: %d.%d.%d.%d\n",
        MA_GET_MAJOR_VERSION( g_agent->agent_version ), MA_GET_MINOR_VERSION( g_agent->agent_version ),
        MA_GET_PATCH_VERSION( g_agent->agent_version ), MA_GET_CUSTOM_VERSION( g_agent->agent_version )
    );

    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "USER-ID: %d\n", g_agent->agent_uid );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "USER-NAME: %s\n", g_agent->user.user_name );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "USER-HOME: %s\n", g_agent->user.user_home );

    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "PROCESS-ID: %d\n", g_agent->agent_pid );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "Current Executable Path: %s\n", g_agent->agent_path );
    snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "Single Instance Path: %s\n", SINGLE_INSTANCE_NAME );

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
}


void proc_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    /*
    GtkWidget *info;
    mild_i8 label[ STRLEN_1024 ] = { 0, };
    printf( "%s clicked\n", __FUNCTION__ );

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
    */
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

    info = ( GtkWidget* )user_data__;

    if( mild_false != getCurrentTimestamp( buf ) )
        snprintf( label, PAGESIZE, "CurrentTimestamp = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    if( mild_false != getCurrentTimestampMn( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentTimestampMn = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    if( mild_false != getCurrentTimeReadable( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentTimeReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

    if( mild_false != getCurrentDateReadable( buf ) )
        snprintf( label + strlen( label ), PAGESIZE - strlen( label ), "CurrentDateReadable = %s\n", buf );
    memset( buf, 0x00, STRLEN_32 );

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
    mild_i8 buf[ STRLEN_16 ] = { 0, };
    mild_i8 label[ STRLEN_1024 ] = { 0, };
    
    if( mild_false != open_sysfs_get_contents( SYSFS_VERSION_FILE, buf, STRLEN_16 ) )
    {
        version = atoi( buf );
        snprintf( label, STRLEN_1024, "openCode Kernel Version: %d.%d.%d.%d\n\n",
            MA_GET_MAJOR_VERSION( version ), MA_GET_MINOR_VERSION( version ),
            MA_GET_PATCH_VERSION( version ), MA_GET_CUSTOM_VERSION( version )
            );
    }

    if( mild_false != open_sysfs_get_contents( SYSFS_INFO_FILE, &info, sizeof( SYSFS_INFO ) ) )
    {
        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "sysfs version : %d.%d.%d.%d\n",
            MA_GET_MAJOR_VERSION( info.sysfs_version ), MA_GET_MINOR_VERSION( info.sysfs_version ),
            MA_GET_PATCH_VERSION( info.sysfs_version ), MA_GET_CUSTOM_VERSION( info.sysfs_version )
            );

        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "netlink version : %d.%d.%d.%d\n",
            MA_GET_MAJOR_VERSION( info.netlink_version ), MA_GET_MINOR_VERSION( info.netlink_version ),
            MA_GET_PATCH_VERSION( info.netlink_version ), MA_GET_CUSTOM_VERSION( info.netlink_version )
            );

        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "Netlink state : %s\n",
            ( mild_false != info.netlink_load ) ? "ONLINE" : "OFFLINE"
            );

        snprintf( label + strlen( label ), STRLEN_1024 - strlen( label ), "Netlink port: %d\n", info.netlink_port );
    }

    if( mild_null == label )
        return;

    info_label = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info_label ), label );
}


void netlink_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    NETLINK_DATA nd = { 0, };
    mild_i8 label[ TWOPAGE ] = { 0, };

    if( 3 > g_agent->netlink_fd )
    {
        if( mild_false == connect_netlink( &g_agent->netlink_fd ) )
            return;
    }

    do
    {
        memset( &nd, 0x00, sizeof( NETLINK_DATA ) );

        if( mild_false == get_netlink_data( g_agent->netlink_fd, &nd ) )
            break;

        if( 0 == strncmp( NETLINK_NO_LOG_MESSAGE, nd.fname, strlen( nd.fname ) ) )
        {
            snprintf( label, TWOPAGE, "%s", NETLINK_NO_LOG_MESSAGE );
            break;
        }

        snprintf( label + strlen( label ), TWOPAGE - strlen( label ), "PID[ %d ] UID[ %d ] TARGET[ %s ] TASK[ %s ]\n\n",
            nd.pid, nd.uid, nd.fname, nd.task );

    } while ( mild_false != nd.remain );
    

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
}
