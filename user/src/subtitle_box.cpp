#include "subtitle_box.h"

#include <iostream>

SubtitleBox::SubtitleBox(
	const std::string& text__
	) : Gtk::Box( Gtk::ORIENTATION_HORIZONTAL ), label_( text__ )
{
	std::cout << "[+] SubtitleBox::SubtitleBox()\n";
	/// 라벨을 SubtitleBox에 추가
	pack_start( label_, Gtk::PACK_EXPAND_WIDGET );
	/// 사용자에게 보여주기
	show( );
	std::cout << "[-] SubtitleBox::SubtitleBox()\n";
}

SubtitleBox::~SubtitleBox( )
{
	std::cout << "SubtitleBox::~SubtitleBox()\n";
}
