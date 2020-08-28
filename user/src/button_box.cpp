#include "button_box.h"

#include <iostream>

ButtonBox::ButtonBox(
	const std::vector<ButtonInfo>& info_list__
	)
		: Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 ), buttons_( )
{
	std::cout << "[+] ButtonBox::ButtonBox()\n";
	/// 버튼 생성 정보가 하나라도 있다면
	if( 0 < info_list__.size( ) )
	{
		/// 실제 GTK Button 객체를 생성 후 벡터에 push
		AddButtons( info_list__ );

		/// 성공적으로 버튼들을 생성하였다면 모두 보여주기
		// show_all_children( true );
		show( );
	}
	std::cout << "[-] ButtonBox::ButtonBox()\n";
}

ButtonBox::~ButtonBox( )
{
	std::cout << "ButtonBox::~ButtonBox()\n";
}

void ButtonBox::AddButtons(
	const std::vector<ButtonInfo>& info_list__
	)
{
	std::cout << "[+] ButtonBox::AddButtons()\n";
	std::unique_ptr<Gtk::Button> button = nullptr;
	
	for( const auto& info : info_list__ )
	{
		/// GTK 버튼 객체 생성
		button = std::make_unique<Gtk::Button>( info.text );
		if( nullptr == button )
			continue;
		
		/// Box에 button을 추가
		pack_start( *button, Gtk::PACK_EXPAND_WIDGET );
		
		/// 생성된 실제 Button 객체를 벡터에 push
		buttons_.emplace_back( std::move( button ) );
		button.reset();
	}

	std::cout << "[-] ButtonBox::AddButtons()\n";
}
