#include "code_gui_init.h"

#include "code_button_handler.h"
#include "code_definitions.h"
#include "code_init.h"


void mainWindow_quit( void )
{
    cleanup_opencode_agent( );

    printf( "openCode exit\n" );
    gtk_main_quit( );
}


void application_quit(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    mainWindow_quit( );
}


void setup_main_window(
    GtkWidget                   *main_window__
    )
{
    g_signal_connect_swapped( 
        G_OBJECT( main_window__ ),
        "destroy",
        G_CALLBACK( mainWindow_quit ),
        NULL
        );

    g_signal_connect_swapped(
        G_OBJECT( main_window__ ),
        "delete_event",
        G_CALLBACK( mainWindow_quit ),
        NULL
        );

    /// 최상위 윈도우로 메인 위젯을 생성
    gtk_container_set_border_width( GTK_CONTAINER( main_window__ ), MAINWINDOW_BORDER );

    /// 메인 위젯의 상단 타이틀을 설정. 존재하지 않으면 기본 문자열로 대체
    /*
    if( mild_false == getConfigListValue( CONFIG_MAIN_TITLE, buf, STRLEN_64 ) )
    {
        memcpy( buf, DEFAULT_AGENT_TITLE, strlen( DEFAULT_AGENT_TITLE ) );
    }
    */
    gtk_window_set_title( GTK_WINDOW( main_window__ ), MAINWINDOW_TITLE );

    /// 3. 메인 윈도우의 가로, 세로 길이를 설정
    gtk_widget_set_size_request( main_window__, MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT );
    /// 4. 메인 윈도우의 시작 위치를 화면 중앙으로 설정
    gtk_window_set_position( GTK_WINDOW( main_window__ ), GTK_WIN_POS_CENTER_ALWAYS );
}


static void setup_contents_widgets(
    GtkWidget                   *c_box__,
    GtkWidget                   *b_box__
    )
{
    GtkWidget *lbl_info;
    GtkWidget *btn_config, *btn_system, *btn_process, *btn_proc, *btn_time, *btn_sysfs, *btn_netlink;

    lbl_info = gtk_label_new( "Test" );

#define SETBTN(w,l,f,c)	{		\
	w=gtk_button_new_with_label(l);	\
	g_signal_connect(G_OBJECT(w),"clicked",G_CALLBACK(f),c);    \
    gtk_widget_set_size_request(w,70,50);   }

    /// 1. 상단 버튼 위젯들을 생성
    SETBTN( btn_config, "Config Info\n(With CRC)", config_button_handler, lbl_info );
    SETBTN( btn_system, "System Info", system_button_handler, lbl_info );
    SETBTN( btn_process, "Process Info", process_button_handler, lbl_info );
    SETBTN( btn_proc, "Proc Info", proc_button_handler, lbl_info );
    SETBTN( btn_time, "Time Info", time_button_handler, lbl_info );
    SETBTN( btn_sysfs, "Sysfs Info", sysfs_button_handler, lbl_info );
    SETBTN( btn_netlink, "Netlink Info", netlink_button_handler, lbl_info );

    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_config, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_system, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_process, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_proc, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_time, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_sysfs, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_netlink, FALSE, TRUE, 0 );

    gtk_box_pack_start( GTK_BOX( c_box__ ), b_box__, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( c_box__ ), lbl_info, FALSE, TRUE, 0 );

#undef SETBTN
}



void setup_agent_widgets(
    GtkWidget                   *mainBox__
    )
{
    GtkWidget *contents_box, *btn_box;
    GtkWidget *lbl_name, *btn_exit;

    lbl_name = gtk_label_new( "openCode Agent" );
    gtk_box_pack_start( GTK_BOX( mainBox__ ), lbl_name, FALSE, TRUE, 0 );

    contents_box = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 );
    btn_box = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );

    setup_contents_widgets( contents_box, btn_box );

    gtk_box_pack_start( GTK_BOX( mainBox__ ), contents_box, FALSE, TRUE, 0 );

    btn_exit = gtk_button_new_with_label( "Exit" );
    gtk_widget_set_size_request( btn_exit, 200,50);
	g_signal_connect( G_OBJECT( btn_exit ), "clicked" , G_CALLBACK( application_quit ), NULL );

    gtk_box_pack_start( GTK_BOX( mainBox__ ), btn_exit, FALSE, TRUE, 0 );
}
