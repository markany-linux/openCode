/**
 * \file		text_window.h
 * 
 * @brief		사용자에게 정보를 보여주는 텍스트 윈도우
 * 
 * \date		2020.09.11.
 * 
 * \author		swma (swma@markany.com)
 * 
 * \copyleft	MarkAny Inc. 2020.
 */
#ifndef __TEXT_WINDOW_H__
#define __TEXT_WINDOW_H__

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>

class TextWindow : public Gtk::ScrolledWindow
{
public:
	/**
	 * @brief	텍스트 창 생성
	 **/
	TextWindow( );

	TextWindow(
		const TextWindow&
		) = delete;
	TextWindow& operator=(
		const TextWindow&
		) = delete;

	TextWindow(
		TextWindow&&
		) = delete;
	TextWindow& operator=(
		TextWindow&&
		) = delete;
	
	/**
	 * @brief	텍스트 창 소멸
	 **/
	virtual ~TextWindow( );

	/**
	 * @brief	텍스트 뷰에서 보여질 텍스트
	 * 
	 * @param	text__	보여질 텍스트
	 * 
	 * @return	true	텍스트가 성공적으로 작성됨
	 * @return	false	텍스트 작성 실패
	 **/
	bool ShowText(
		const std::string&		text__
		);

private:
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
