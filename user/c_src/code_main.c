#include "common.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "code_init.h"
#include "code_gui_init.h"

/// agent management info.
POPENCODE_AGENT g_agent;


int main(
    int                         argc__,
    char                        **argv__
    )
{
    //mild_i32 init_error = 0;
    GtkWidget *mainBox;

    printf( "Hello openCode\n" );

    gtk_init( &argc__, &argv__ );

    /// openCode 초기화
    if( mild_false == init_opencode_agent( &g_agent ) )
    {
        /// TODO: 메시지 박스로 에러 출력하도록 수정
        printf( "openCode initialize fail\n" );
        return -1;
    }

    /// 메인 윈도우 위젯 생성
    g_agent->ui.mainWindow = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    setup_main_window( g_agent->ui.mainWindow );

    mainBox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );
    setup_agent_widgets( mainBox );

    /// 5. 메인 박스를 메인 윈도우에 포함하고, 화면에 표시
    gtk_container_add( GTK_CONTAINER( g_agent->ui.mainWindow ), mainBox );
    gtk_widget_show_all( g_agent->ui.mainWindow );


    /// openCode 종료
    //cleanup_opencode_agent( g_agent );

    gtk_main( );

    return 0;
}
