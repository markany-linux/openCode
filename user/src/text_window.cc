#include "text_window.h"

#include <iostream>

TextWindow::TextWindow( )
	: Gtk::ScrolledWindow( ),
	  text_view_box_( ),
	  text_view_( ),
	  text_buffer_( )
{
	std::cout << "[+] TextWindow::TextWindow()\n";
	/// 사용자가 직접 텍스트 내용을 수정하지 못하도록 설정
	text_view_.set_editable( false );
	text_view_.set_can_focus( false );
	
	/// 텍스트 뷰 박스를 스크롤 가능한 윈도우에 삽입
	AppendTextViewBox( );
	std::cout << "[-] TextWindow::TextWindow()\n";
}

TextWindow::~TextWindow( )
{
	std::cout << "TextWindow::TextWindow()\n";
}

bool TextWindow::ShowText(
		std::string text__
	)
{
	std::cout << "[+] TextWindow::AddText()\n";
	/// 만약 텍스트 버퍼가 할당된 적 없는 경우 최초 할당 시도
	if( !text_buffer_ )
	{
		text_buffer_ = Gtk::TextBuffer::create( );
		/// 할당에 실패했다면 텍스트 추가 실패로 알림.
		if( !text_buffer_ )
		{
			std::cout << "Failed to allocate memory for text writing.\n";
			return false;
		}

		/// 텍스트 뷰에 생성된 텍스트 버퍼 지정
		text_view_.set_buffer( text_buffer_ );
	}

	/// 자동으로 텍스트 뷰에 업데이트 됨
	text_buffer_->set_text( text__ );
	std::cout << "[-] TextWindow::AddText()\n";
	return true;
}

void TextWindow::AppendTextViewBox( )
{
	std::cout << "[+] TextWindow::AppendTextViewBox()\n";
	text_view_box_.pack_start( text_view_ );
	add( text_view_box_ );
	std::cout << "[-] TextWindow::AppendTextViewBox()\n";
}
