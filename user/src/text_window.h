#ifndef __TEXT_BOX_H__
#define __TEXT_BOX_H__

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>

class TextWindow : public Gtk::ScrolledWindow
{
public:
	/**
	 * @brief	텍스트 창 생성
	 * 
	 * @param	editable__	사용자가 직접 텍스트 내용을 수정 가능한지에 대한 여부
	 * 						(true: 가능, false 불가능)
	 **/
	explicit TextWindow(
		bool editable__
		);
	
	/**
	 * @brief	텍스트 창 소멸
	 **/
	virtual ~TextWindow( );

	/**
	 * @brief	텍스트 뷰에서 보여질 텍스트 추가
	 * 
	 * @param	text__	붙여질 텍스트
	 * 
	 * @return	텍스트가 성공적으로 쓰였다면 true, 아닐 경우 false
	 **/
	bool AddText(
		std::string text__
		);

protected:
	/**
	 * @brief	텍스트 뷰 박스를 스크롤 가능한 윈도우에 삽입
	 **/
	void AppendTextViewBox( );

	/// 텍스트 뷰를 담을 박스
	Gtk::Box text_view_box_;
	/// 텍스트 뷰 객체
	Gtk::TextView text_view_;
	/// 텍스트 뷰에서 표시할 텍스트의 버퍼
	Glib::RefPtr<Gtk::TextBuffer> text_buffer_;
};

#endif
