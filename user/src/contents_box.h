#ifndef __CONTENT_BOX_H__
#define __CONTENT_BOX_H__

#include <gtkmm/box.h>

#include "button_box.h"
#include "text_window.h"

class ContentsBox : public Gtk::Box
{
public:
	/**
	 * @brief	각종 컨텐츠들을 삽입할 박스 생성
	 * 
	 * @param	info_list__		버튼 생성 정보들이 담긴 벡터
	 * @param	text_editable__	텍스트 창의 내용을 사용자가 수정할 수 있는 지에 대한 여부
	 */
	explicit ContentsBox(
		const std::vector<ButtonInfo>& info_list__,
		bool text_editable__
		);
	
	/**
	 * @brief	컨텐트 박스 소멸
	 **/
	virtual ~ContentsBox( );

protected:
	/**
	 * @brief	각종 컨텐츠들을 삽입
	 **/
	void AppendContents( );

	/// 버튼 박스
	ButtonBox button_box_;
	/// 텍스트 창
	TextWindow text_window_;

private:
	ContentsBox(
		const ContentsBox&
		) = delete;
	ContentsBox(
		const ContentsBox&&
		) = delete;
};

#endif
