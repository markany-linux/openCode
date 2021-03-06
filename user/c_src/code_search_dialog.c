#include "code_search_dialog.h"

#include "code_init.h"


/**
 * @brief   다이얼로그에서 발생하는 시그널에 정보를 전달하기 위한 구조체
 */
typedef struct widget_set_struct
{
    /// 사용자 입력 창 위젯
    GtkWidget                   *entry;

    /// 라벨 위젯
    GtkWidget                   *label;

    /// 다이얼로그 위젯
    GtkWidget                   *dialog;

} TRIPLE_WIDGET, *PTRIPLE_WIDGET;


/**
 * @brief   커널 심볼을 찾는 기능
 * 
 * @param   this__      호출한 위젯
 * @param   user_data__ 추가 전달 정보
 */
static void search_ksyms(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    mild_i8 buf[ STRLEN_64 ] = { 0, };
    const gchar *txt_symbol = mild_null;
    PTRIPLE_WIDGET param = mild_null;

    /// 추가 정보를 획득
    param = ( PTRIPLE_WIDGET )user_data__;

    /// 사용자 입력 창의 내용을 획득
    txt_symbol = gtk_entry_get_text( GTK_ENTRY( param->entry ) );

    /// 사용자 입력 여부 확인
    if( 0 == strlen( txt_symbol ) )
    {
        /// 사용자 입력이 없는 경우의 처리
        gtk_label_set_text( GTK_LABEL( param->label ), "Enter search symbol name" );
        return;
    }

    /// 요청 심볼 존재 여부 확인
    if( mild_false == checkKernelSymbolExist( txt_symbol, mild_null ) )
    {
        /// 존재하지 않는 경우의 처리. 심볼 미존재를 라벨에 출력
        snprintf( buf, STRLEN_64, "[ %s ] symbol not exists", txt_symbol );
        gtk_label_set_text( GTK_LABEL( param->label ), buf );
        return;
    }

    /// 요청 심볼 존재를 라벨에 출력
    snprintf( buf, STRLEN_64, "[ %s ] symbol exists", txt_symbol );
    gtk_label_set_text( GTK_LABEL( param->label ), buf );
}


/**
 * @brief   커널 모듈 찾는 기능
 * 
 * @param   this__      호출 위젯
 * @param   user_data__ 추가 전달 정보
 */
static void search_module(
    GtkWidget                   *this__,
    gpointer                    user_data__
    )
{
    mild_i8 buf[ STRLEN_64 ] = { 0, };
    const gchar *txt_module = mild_null;
    PTRIPLE_WIDGET param = mild_null;

    /// 추가 정보 획득
    param = ( PTRIPLE_WIDGET )user_data__;

    /// 사용자 입력 정보 획득
    txt_module = gtk_entry_get_text( GTK_ENTRY( param->entry ) );

    /// 입력 정보 존재 여부 확인
    if( 0 == strlen( txt_module ) )
    {
        /// 입력하지 않는 경우의 처리
        gtk_label_set_text( GTK_LABEL( param->label ), "Enter search module name" );
        return;
    }

    /// 커널 모듈 존재 확인
    if( mild_false == checkKernelModuleExist( txt_module ) )
    {
        /// 존재하지 않는 경우의 처리
        snprintf( buf, STRLEN_64, "[ %s ] module isNot exists", txt_module );
        gtk_label_set_text( GTK_LABEL( param->label ), buf );
        return;
    }

    /// 요청한 커널 모듈이 존재하는 경우의 처리
    snprintf( buf, STRLEN_64, "[ %s ] module EXIST", txt_module );
    gtk_label_set_text( GTK_LABEL( param->label ), buf );
}


/**
 * @brief   다이얼로그의 버튼 클릭 처리기
 * 
 * @param   this__      클릭된 위젯
 * @param   response__  위젯 정보
 * @param   user_data__ 추가 전달 정보
 */
static void search_dispatcher(
    GtkWidget                   *this__,
    gint                        response__,
    gpointer                    user_data__
    )
{
    /// CANCEL 버튼 입력 여부 확인
    if( GTK_RESPONSE_REJECT == response__ )
    {
        /// CANCEL 버튼 입력 시 다이얼로그를 해제하고 종료
        gtk_widget_destroy( this__ );
        return;
    }
}


void search_dialog_run( void )
{
    GtkWidget *dialog, *contents;
    GtkWidget *lbl_ksyms, *entry_ksyms, *lbl_mod, *entry_mod;
    GtkWidget *lbl_result;
    GtkWidget *btn_ksyms, *btn_mod;
    GtkWidget *kbox, *mbox;
    TRIPLE_WIDGET ksyms_widget = { 0, };
    TRIPLE_WIDGET mod_widget = { 0, };

    /// 다이얼로그 생성
    dialog = gtk_dialog_new_with_buttons(
        "Search Dialog",
        GTK_WINDOW( g_agent->ui.mainWindow ),
        GTK_DIALOG_MODAL,
        "_CANCEL",
        GTK_RESPONSE_REJECT,
        NULL
        );

    /// 라벨 생성
    lbl_result = gtk_label_new( "Search Result" );
    lbl_ksyms = gtk_label_new( "Search Symbol: " );
    lbl_mod = gtk_label_new( "Search Module: " );

    /// 입력받을 Entry 생성 및 길이 제한
    entry_ksyms = gtk_entry_new( );
    gtk_entry_set_max_length( GTK_ENTRY( entry_ksyms ), STRLEN_32 );
    entry_mod = gtk_entry_new( );
    gtk_entry_set_max_length( GTK_ENTRY( entry_mod ), STRLEN_32 );

    /// 커널 심볼 탐색 처리를 위해 필요한 위젯 정보 수집
    ksyms_widget.entry = entry_ksyms;
    ksyms_widget.label = lbl_result;
    ksyms_widget.dialog = dialog;

    /// 커널 모듈 탐색 처리를 위해 필요한 위젯 정보 수집
    mod_widget.entry = entry_mod;
    mod_widget.label = lbl_result;
    mod_widget.dialog = dialog;

    /// 커널 심볼 검색 버튼 생성 및 클릭 핸들러 등록
    btn_ksyms = gtk_button_new_with_label( "Search Symbol" );
    g_signal_connect( G_OBJECT( btn_ksyms ), "clicked", G_CALLBACK( search_ksyms ), &ksyms_widget );

    /// 커널 모듈 검색 버튼 생성 및 클릭 핸들러 등록
    btn_mod = gtk_button_new_with_label( "Search Module" );
    g_signal_connect( G_OBJECT( btn_mod ), "clicked", G_CALLBACK( search_module ), &mod_widget );

    /// 커널 심볼/모듈 탐색을 위한 위젯들을 포함할 박스 생성
    kbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 );
    mbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 );

    /// 생성된 커널 심볼 탐색 위젯들을 박스에 패킹
    gtk_box_pack_start( GTK_BOX( kbox ), lbl_ksyms, FALSE, FALSE, 0 );
    gtk_box_pack_start( GTK_BOX( kbox ), entry_ksyms, FALSE, FALSE, 0 );
    gtk_box_pack_start( GTK_BOX( kbox ), btn_ksyms, FALSE, FALSE, 0 );

    /// 생성된 커널 모듈 탐색 위젯들을 박스에 패킹
    gtk_box_pack_start( GTK_BOX( mbox ), lbl_mod, FALSE, FALSE, 0 );
    gtk_box_pack_start( GTK_BOX( mbox ), entry_mod, FALSE, FALSE, 0 );
    gtk_box_pack_start( GTK_BOX( mbox ), btn_mod, FALSE, FALSE, 0 );

    /// 다이얼로그의 컨텐츠 영역을 획득하여 생성된 각 위젯들을 패킹
    contents = gtk_dialog_get_content_area( GTK_DIALOG( dialog ) );
    gtk_container_add( GTK_CONTAINER( contents ), kbox );
    gtk_container_add( GTK_CONTAINER( contents ), mbox );
    gtk_container_add( GTK_CONTAINER( contents ), lbl_result );

    /// 커널 심볼 탐색 입력 entry에 Enter 키가 눌린 경우를 처리하기 위한 핸들러 등록
    g_signal_connect( GTK_ENTRY( entry_ksyms ), "activate", G_CALLBACK( search_ksyms ), &ksyms_widget );
    /// 커널 모듈 탐색 입력 entry에 Enter 키가 눌린 경우를 처리하기 위한 핸들러 등록
    g_signal_connect( GTK_ENTRY( entry_mod ), "activate", G_CALLBACK( search_module ), &mod_widget );

    /// 다이얼로그의 CANCEL 버튼 입력 시 처리할 핸들러 등록
    g_signal_connect( GTK_DIALOG( dialog ), "response", G_CALLBACK( search_dispatcher ), NULL );

    /// 다이얼로그를 표시하고 실행
    gtk_widget_show_all( dialog );
    gtk_dialog_run( GTK_DIALOG( dialog ) );
}

