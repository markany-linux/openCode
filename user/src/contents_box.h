#ifndef __CONTENT_BOX_H__
#define __CONTENT_BOX_H__

#include <gtkmm/box.h>

#include "button_box.h"
#include "text_window.h"

class AgentWindow;

class ContentsBox : public Gtk::Box
{
public:
	/**
	 * @brief	각종 컨텐츠들을 삽입할 박스 생성
	 * 
	 * @param	info_list__		버튼 생성 정보들이 담긴 벡터
	 * @param	text_editable__	텍스트 창의 내용을 사용자가 수정할 수 있는 지에 대한 여부
	 */
	ContentsBox( );
	
	/**
	 * @brief	컨텐트 박스 소멸
	 **/
	virtual ~ContentsBox( );

	ContentsBox(
		const ContentsBox&
		) = delete;
	ContentsBox& operator=(
		const ContentsBox&
		) = delete;

	ContentsBox(
		ContentsBox&&
		) = delete;
	ContentsBox& operator=(
		ContentsBox&&
		) = delete;

protected:
	/**
	 * @brief	각종 컨텐츠들을 삽입
	 **/
	void AppendContents( );

private:
	/// 버튼 박스
	ButtonBox button_box_{ this };
	/// 텍스트 창
	TextWindow text_window_;
};

#endif
