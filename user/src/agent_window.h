#ifndef __AGENT_WINDOW_H__
#define __AGENT_WINDOW_H__

#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "contents_box.h"
#include "subtitle_box.h"

class AgentWindow : public Gtk::Window
{
public:
	/**
	 * @brief	메인 윈도우 객체 생성
	 **/
	AgentWindow( );
	
	/**
	 * @brief	메인 윈도우 객체 소멸
	 **/
	virtual ~AgentWindow( );

protected:
	/// 종료 버튼 텍스트 상수
	static constexpr const char* kQuitButtonText = "종료";
	static constexpr int kWindowWidth = 300;
	static constexpr int kWindowHeight = 400;
	static constexpr const char* kTitle = "openCode Agent";

	/**
	 * @brief	메인 박스에 파생 위젯 attach
	 **/
	void AttachChildWidgets( );

	/**
	 * @brief	종료 버튼 생성
	 **/
	void AttachQuitButton( );

	/**
	 * @brief	종료 버튼 클릭 이벤트 핸들러
	 **/
	void on_quit_button_clicked( );

	/// 가장 최상단의 박스
	Gtk::Box main_box_{ Gtk::ORIENTATION_VERTICAL };
	/// 상단 라벨 박스
	Gtk::Label subtitle_;
	/// 각종 컨텐츠가 들어간 박스
	ContentsBox contents_box_;

	/// 종료 박스
	Gtk::Box quit_box_;
	/// 종료 버튼
	Gtk::Button quit_button_{ kQuitButtonText };
};

#endif

