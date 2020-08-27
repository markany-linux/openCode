#include "main_window.h"

#include <iostream>
#include <tuple>

MainWindow::MainWindow(
	const std::string& subtitle__,
	const std::vector<ButtonInfo>& button_list__,
	const Glib::RefPtr<Gtk::Application> app__
	)
		: app_( app__ ),
		  main_box_( Gtk::ORIENTATION_VERTICAL ),
		  subtitle_( subtitle__ ), button_box_( button_list__ ),
		  quit_box_( ), quit_button_( kQuitButtonText )
		 
{
	std::cout << "[+] MainWindow::MainWindow()\n";
	/// 사용자가 임의로 종료를 시도할 때에 대한 핸들러 등록
	signal_delete_event( )
		.connect( sigc::mem_fun( *this, &MainWindow::on_delete_event ) );

	/// 메인 박스에 파생 위젯들을 attach
	AttachChildWidgets( );
	/// 메인 박스를 메인 윈도우에 추가
	add( main_box_ );
	
	/// 모든 객체 보여주기
	show_all_children( );
	std::cout << "[-] MainWindow::MainWindow()\n";
}

MainWindow::~MainWindow( )
{
	std::cout << "MainWindow::~MainWindow()\n";
}

void MainWindow::AttachChildWidgets( )
{
	std::cout << "[+] MainWindow::AttachChildWidgets()\n";
	/// 상단 제목 라벨 메인 박스에 추가
	main_box_.pack_start( subtitle_ );
	/// 버튼 박스 메인 박스에 추가
	main_box_.pack_start( button_box_ );

	AttachQuitButton( );
	std::cout << "[-] MainWindow::AttachChildWidgets()\n";
}

void MainWindow::AttachQuitButton( )
{
	std::cout << "[+] MainWindow::AttachQuitButton()\n";
	quit_button_.signal_clicked( )
		.connect( sigc::mem_fun( *this,
								 &MainWindow::on_quit_button_clicked ) );
	/// 박스에 종료 버튼을 붙임
	quit_box_.pack_start( quit_button_, Gtk::PACK_EXPAND_PADDING );
	/// 메인 박스에 종료 버튼이 담긴 박스를 붙임
	main_box_.pack_start( quit_box_, Gtk::PACK_SHRINK );
	std::cout << "[-] MainWindow::AttachQuitButton()\n";
}

bool MainWindow::on_delete_event(
	GdkEventAny* any_event__
	)
{
	std::cout << "[+] MainWindow::on_delete_event()\n";
	/// any_event는 아직 꼭 사용해야 하는 것은 아님.
	std::ignore = any_event__;
	std::cout << "[-] MainWindow::on_delete_event()\n";
	/// 종료 명령 무시
	return true;
}

void MainWindow::on_quit_button_clicked( )
{
	std::cout << "[+] MainWindow::on_quit_button_clicked()\n";
	std::cout << "Bye bye\n";
	/// 프로그램 종료
	app_->quit( );
	std::cout << "[-] MainWindow::on_quit_button_clicked()\n";
}
