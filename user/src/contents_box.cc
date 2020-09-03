#include "contents_box.h"
#include "gtkmm/box.h"

#include <iostream>

ContentsBox::ContentsBox( )
{
	std::cout << "[+] ContentBox::ContentBox()\n";
	/// 각종 컨텐츠를 컨텐트 박스에 추가
	AppendContents( );
	std::cout << "[-] ContentBox::ContentBox()\n";
}

ContentsBox::~ContentsBox( )
{
	std::cout << "ContentBox::~ContentBox()\n";
}

void ContentsBox::AppendContents( )
{
	std::cout << "[+] ContentBox::AppendContents()\n";
	/// 버튼 박스 추가
	pack_start( button_box_, Gtk::PACK_SHRINK, 20 );
	/// 텍스트 창 추가
	pack_start( text_window_ );
	std::cout << "[-] ContentBox::AppendContents()\n";
}
