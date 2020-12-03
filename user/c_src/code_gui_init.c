#include "code_gui_init.h"

#include "code_button_handler.h"
#include "code_definitions.h"
#include "code_init.h"


/**
 * @brief   최상위 윈도우 종료 처리기
 */
static void mainWindow_quit( void )
{
    /// 에이전트 정리 함수 호출
    cleanup_opencode_agent( );

    printf( "openCode exit\n" );

    /// GTK application 종료
    gtk_main_quit( );
}


/**
 * @brief   응용 프로그램 종료 처리기
 *          GTK 종료 시그널을 처리하기 위해 선언
 *          내부적으로 최상위 윈도우 종료 처리기를 호출
 * 
 * @param   this__      최상위 윈도우 위젯
 * @param   user_data__ 추가 데이터
 */
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
    /// 최상위 윈도우 파괴 시그널 처리 핸들러 교체
    g_signal_connect_swapped( 
        G_OBJECT( main_window__ ),
        "destroy",
        G_CALLBACK( mainWindow_quit ),
        NULL
        );

    /// 최상위 윈도우 종료 이벤트 시그널 처리 핸들러 교체
    g_signal_connect_swapped(
        G_OBJECT( main_window__ ),
        "delete_event",
        G_CALLBACK( mainWindow_quit ),
        NULL
        );

    /// 최상위 윈도우로 메인 위젯을 생성
    gtk_container_set_border_width( GTK_CONTAINER( main_window__ ), MAINWINDOW_BORDER );

    /// 메인 위젯의 상단 타이틀을 설정. 존재하지 않으면 기본 문자열로 대체
    /// 사용할 경우, 문자열 버퍼를 선언하고 주석 제거 후 사용
    /*
    /// 상단 타이틀을 설정 파일에서 읽어 들임
    if( mild_false == getConfigListValue( CONFIG_MAIN_TITLE, buf, STRLEN_64 ) )
    {
        /// 실패 시, 기본 타이틀을 사용
        memcpy( buf, DEFAULT_AGENT_TITLE, strlen( DEFAULT_AGENT_TITLE ) );
        gtk_window_set_title( GTK_WINDOW( main_window__ ), MAINWINDOW_TITLE );
    }
    else
    {
        gtk_window_set_title( GTK_WINDOW( main_window__ ), buf );
    }
    */
    /// 기본 값으로 메인 타이틀 설정. 설정 파일을 이용할 경우 주석 처리
    gtk_window_set_title( GTK_WINDOW( main_window__ ), MAINWINDOW_TITLE );

    /// 메인 윈도우의 가로, 세로 길이를 설정
    gtk_widget_set_size_request( main_window__, MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT );
    /// 메인 윈도우의 시작 위치를 항상 화면 중앙으로 설정
    gtk_window_set_position( GTK_WINDOW( main_window__ ), GTK_WIN_POS_CENTER_ALWAYS );
}


/**
 * @brief   에이전트에 버튼들과 정보 라벨을 생성하여 패킹
 * 
 * @param   c_box__ 컨텐츠 박스
 * @param   b_box__ 버튼 박스
 */
static void setup_contents_widgets(
    GtkWidget                   *c_box__,
    GtkWidget                   *b_box__
    )
{
    GtkWidget *lbl_info;
    GtkWidget *btn_config, *btn_system, *btn_process, *btn_proc, *btn_time, *btn_sysfs, *btn_netlink;

    /// 정보 라벨에 기본 문자열을 입력하여 생성
    lbl_info = gtk_label_new( "Test" );

/// 버튼 생성 매크로 선언
#define SETBTN(w,l,f,c)	{		\
	w=gtk_button_new_with_label(l);	\
	g_signal_connect(G_OBJECT(w),"clicked",G_CALLBACK(f),c);    \
    gtk_widget_set_size_request(w,70,50);   }

    /// 버튼 위젯들을 생성. 추가 데이터로 정보 라벨을 전달하도록 구성
    SETBTN( btn_config, "Config Info\n(With CRC)", config_button_handler, lbl_info );
    SETBTN( btn_system, "System Info", system_button_handler, lbl_info );
    SETBTN( btn_process, "Process Info", process_button_handler, lbl_info );
    SETBTN( btn_proc, "Proc Info", proc_button_handler, lbl_info );
    SETBTN( btn_time, "Time Info", time_button_handler, lbl_info );
    SETBTN( btn_sysfs, "Sysfs Info", sysfs_button_handler, lbl_info );
    SETBTN( btn_netlink, "Netlink Info", netlink_button_handler, lbl_info );

    /// 생성된 버튼들을 버튼 박스에 입력
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_config, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_system, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_process, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_proc, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_time, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_sysfs, FALSE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( b_box__ ), btn_netlink, FALSE, TRUE, 0 );

    /// 컨텐츠 박스에 버튼 박스를 패킹
    gtk_box_pack_start( GTK_BOX( c_box__ ), b_box__, FALSE, TRUE, 0 );
    /// 컨텍츠 박스에 정보 라벨을 패킹
    gtk_box_pack_start( GTK_BOX( c_box__ ), lbl_info, FALSE, TRUE, 0 );

/// 버튼 생성 매크로 해제
#undef SETBTN
}


void setup_agent_widgets(
    GtkWidget                   *mainBox__
    )
{
    GtkWidget *contents_box, *btn_box;
    GtkWidget *lbl_name, *btn_exit;

    /// 최상단에 출력할 정보 라벨 생성 및 패킹
    lbl_name = gtk_label_new( "openCode Agent" );
    gtk_box_pack_start( GTK_BOX( mainBox__ ), lbl_name, FALSE, TRUE, 0 );

    /// 컨텐츠 박스 생성
    contents_box = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 );
    /// 버튼 박스 생성
    btn_box = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );

    /// 생성된 컨텐츠, 버튼 박스에 위젯들을 생성하여 입력
    setup_contents_widgets( contents_box, btn_box );

    /// 메인 박스에 설정된 컨텐츠 박스를 패킹
    gtk_box_pack_start( GTK_BOX( mainBox__ ), contents_box, FALSE, TRUE, 0 );

    /// 종료 버튼 생성 및 설정
    btn_exit = gtk_button_new_with_label( "Exit" );
    /// 종료 버튼 크기 설정
    gtk_widget_set_size_request( btn_exit, 200,50);
    /// 종료 버튼 시그널 처리
	g_signal_connect( G_OBJECT( btn_exit ), "clicked" , G_CALLBACK( application_quit ), NULL );

    /// 메인 박스에 종료 버튼 패킹
    gtk_box_pack_start( GTK_BOX( mainBox__ ), btn_exit, FALSE, TRUE, 0 );
}
