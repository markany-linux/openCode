#include "agent_window.h"

#include <iostream>
#include <tuple>

#include <gtkmm/box.h>

AgentWindow::AgentWindow( )
{
	std::cout << "[+] AgentWindow::AgentWindow()\n";
	/// 사용자가 임의로 종료를 시도할 때에 대한 핸들러 등록
	signal_delete_event( )
		.connect( sigc::mem_fun( *this, &AgentWindow::on_delete_event ) );

	/// 메인 박스에 파생 위젯들을 attach
	AttachChildWidgets( );
	/// 메인 박스를 메인 윈도우에 추가
	add( main_box_ );

	/// 기본 창 사이즈 설정
	set_default_size( kWindowWidth, kWindowHeight );

	/// 사용자 임의로 창 크기 조절하는 것 방지
	set_resizable( false );
	
	/// 모든 객체 보여주기
	show_all_children( true );
	std::cout << "[-] AgentWindow::AgentWindow()\n";
}

AgentWindow::~AgentWindow( )
{
	std::cout << "AgentWindow::~AgentWindow()\n";
}

void AgentWindow::AttachChildWidgets( )
{
	std::cout << "[+] AgentWindow::AttachChildWidgets()\n";
	/// 상단 제목 라벨 메인 박스에 추가
	main_box_.pack_start( subtitle_box_, Gtk::PACK_SHRINK, 20 );
	/// 버튼 박스 메인 박스에 추가
	main_box_.pack_start( contents_box_ );
	/// 종료 버튼 메인 박스에 추가
	AttachQuitButton( );
	std::cout << "[-] AgentWindow::AttachChildWidgets()\n";
}

void AgentWindow::AttachQuitButton( )
{
	std::cout << "[+] AgentWindow::AttachQuitButton()\n";
	/// 종료 버튼 클릭 이벤트에 핸들러 등록
	quit_button_.signal_clicked( )
				.connect(
					sigc::mem_fun( *this,
								   &AgentWindow::on_quit_button_clicked ) );
	/// 박스에 종료 버튼을 붙임
	quit_box_.pack_start( quit_button_, Gtk::PACK_EXPAND_PADDING );
	/// 메인 박스에 종료 버튼이 담긴 박스를 붙임
	main_box_.pack_start( quit_box_, Gtk::PACK_SHRINK, 20 );
	std::cout << "[-] AgentWindow::AttachQuitButton()\n";
}

void AgentWindow::on_quit_button_clicked( )
{
	std::cout << "[+] AgentWindow::on_quit_button_clicked()\n";
	/// 에이전트 창 종료
	hide( );
	std::cout << "[-] AgentWindow::on_quit_button_clicked()\n";
}

