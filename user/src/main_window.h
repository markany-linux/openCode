#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <gtkmm/window.h>

#include "button_box.h"
#include "subtitle_box.h"

class MainWindow : public Gtk::Window
{
public:
	/**
	 * @brief	메인 윈도우 객체 생성
	 * 
	 * @param	subtitle__		상단 라벨 텍스트
	 * @param	button_list__	버튼 생성 정보들을 담은 벡터
	 **/
	explicit MainWindow(
		const std::string& subtitle__,
		const std::vector<ButtonInfo>& button_list__
		);
	
	/**
	 * @brief	메인 윈도우 객체 소멸
	 **/
	virtual ~MainWindow( );

protected:
	/**
	 * @brief	사용자가 임의로 종료를 시도할 시 호출되는 핸들러
	 * 
	 * @param	any_event__	TODO: 설명 추가 필요
	 **/
	bool on_delete_event(
		GdkEventAny* any_event__
		);

	Gtk::Box main_box_; /// 가장 최상단의 박스
	Subtitle subtitle_; /// 상단 라벨 박스
	ButtonBox button_box_; /// 버튼들이 들어간 박스
};

#endif
