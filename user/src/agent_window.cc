#include "agent_window.h"

#include <iostream>
#include <tuple>

#include <gtkmm/box.h>

#include "agent_main.h"
#include "button_box.h"

AgentWindow::AgentWindow( ) : button_box_( text_window_ )
{
	constexpr int kMargin = 20;
	std::cout << "[+] AgentWindow::AgentWindow()\n";

	/// 메인 박스에 파생 위젯들을 attach
	AttachChildWidgets( );

	main_box_.set_margin_start( kMargin );
	main_box_.set_margin_end( kMargin );

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

void AgentWindow::ShowText(
	const std::string&		text__
	)
{
	std::cout << "[+] AgentWindow::ShowText()\n";
	text_window_.ShowText( text__ );
	std::cout << "[-] AgentWindow::ShowText()\n";
}

void AgentWindow::AttachChildWidgets( )
{
	std::cout << "[+] AgentWindow::AttachChildWidgets()\n";
	/// 상단 제목 라벨 메인 박스에 추가
	main_box_.pack_start( subtitle_, Gtk::PACK_SHRINK, 20 );
	main_box_.pack_start( contents_box_ );

	/// 버튼 박스 컨텐츠 박스에 추가
	AttachContentsToContentsBox( );
	/// 종료 버튼 메인 박스에 추가
	AttachQuitButton( );
	std::cout << "[-] AgentWindow::AttachChildWidgets()\n";
}

void AgentWindow::AttachContentsToContentsBox( )
{
	/// 정보 표시를 요청할 수 있는 버튼들 추가
	contents_box_.pack_start( button_box_, Gtk::PACK_SHRINK, 50 );
	/// 정보들을 표시할 텍스트 뷰 윈도우 추가
	contents_box_.pack_start( text_window_, Gtk::PACK_EXPAND_WIDGET );
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

