#include "code_button_handler.h"

#include "code_init.h"
#include "code_definitions.h"


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
    mild_i8 label[ STRLEN_1024 ] = { 0, };
    printf( "%s clicked\n", __FUNCTION__ );

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
}



void proc_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 label[ STRLEN_1024 ] = { 0, };
    printf( "%s clicked\n", __FUNCTION__ );

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
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
    mild_i32 fd = 0;
    GtkWidget *info;
    mild_i8 label[ STRLEN_1024 ] = { 0, };

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
}



void netlink_button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    GtkWidget *info;
    mild_i8 label[ STRLEN_1024 ] = { 0, };

    printf( "%s clicked\n", __FUNCTION__ );

    info = ( GtkWidget* )user_data__;

    gtk_label_set_text( GTK_LABEL( info ), label );
}


/*
void _button_handler(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    printf( "%s clicked\n", __FUNCTION__ );
}
*/

