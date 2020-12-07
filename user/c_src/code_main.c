#include "common.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "code_init.h"
#include "code_gui_init.h"

/// 에이전트 정보 전역 변수
POPENCODE_AGENT g_agent;


int main(
    int                         argc__,
    char                        **argv__
    )
{
    GtkWidget *mainBox;

    /// GTK 프로그램 시작
    gtk_init( &argc__, &argv__ );

    /// openCode 에이전트 초기화
    if( mild_false == init_opencode_agent( &g_agent ) )
    {
        printf( "openCode initialize fail\n" );
        return -1;
    }

    /// 최상위 윈도우 위젯 생성
    g_agent->ui.mainWindow = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    /// 최상위 윈도우 설정
    setup_main_window( g_agent->ui.mainWindow );

    /// 메인 박스 생성
    mainBox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );
    /// 메인 박스에 컨텐츠들을 생성하여 패킹
    setup_agent_widgets( mainBox );

    /// 메인 박스를 메인 윈도우에 포함하고, 화면에 표시
    gtk_container_add( GTK_CONTAINER( g_agent->ui.mainWindow ), mainBox );
    /// 최상위 윈도우에 포함된 모든 위젯을 화면에 표시
    gtk_widget_show_all( g_agent->ui.mainWindow );

    printf( "Hello openCode\n" );
    /// GTK 프로그램 실행 루프 시작
    gtk_main( );

    return 0;
}
