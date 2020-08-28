#include "button_box.h"
#include "contents_box.h"

#include <iostream>

ButtonBox::ButtonBox(
	ContentsBox* contents_box__,
	const std::vector<ButtonInfo>& info_list__
	)
		: Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 ),
		  buttons_( ),
		  contents_box_( contents_box__)
{
	std::cout << "[+] ButtonBox::ButtonBox()\n";
	/// 버튼 생성 정보가 하나라도 있다면
	if( 0 < info_list__.size( ) )
		AddButtons( info_list__ ); /// 실제 GTK Button 객체를 생성 후 벡터에 push
	
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
		pack_start( *button, Gtk::PACK_EXPAND_PADDING );
		button->signal_clicked()
				.connect(
					sigc::bind(
						sigc::mem_fun( *this,
										 &ButtonBox::on_button_clicked ),
						button.get() ) );
		
		/// 생성된 실제 Button 객체를 벡터에 push
		buttons_.emplace_back( std::move( button ) );
		button.reset();
	}

	std::cout << "[-] ButtonBox::AddButtons()\n";
}

void ButtonBox::on_button_clicked( Gtk::Button* button__ )
{
	contents_box_->text_window_.AddText( button__->get_label() );
}
