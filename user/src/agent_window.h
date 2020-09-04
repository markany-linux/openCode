#ifndef __AGENT_WINDOW_H__
#define __AGENT_WINDOW_H__

#include <gtkmm/box.h>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "button_box.h"
#include "text_window.h"

class AgentMain;

class AgentWindow : public Gtk::Window
{
public:
	/**
	 * @brief	메인 윈도우 객체 생성
	 **/
	AgentWindow(
		AgentMain*				agent_main__
		);
	
	/**
	 * @brief	메인 윈도우 객체 소멸
	 **/
	virtual ~AgentWindow( );

protected:
	/// 종료 버튼 텍스트 상수
	static constexpr const char* kQuitButtonText = "종료";
	static constexpr int kWindowWidth = 600;
	static constexpr int kWindowHeight = 500;
	static constexpr const char* kTitle = "openCode Agent";

	/**
	 * @brief	메인 박스에 파생 박스/위젯들을 attach
	 **/
	void AttachChildWidgets( );

	/**
	 * @brief	종료 버튼 생성
	 **/
	void AttachQuitButton( );

	/**
	 * @brief	컨텐츠 박스에 사용자 입력/출력 관련 위젯들을 attach
	 **/
	void AttachContentsToContentsBox( );

	/**
	 * @brief	종료 버튼 클릭 이벤트 핸들러
	 **/
	void on_quit_button_clicked( );

	/// 가장 최상단의 세로 박스
	Gtk::Box main_box_{ Gtk::ORIENTATION_VERTICAL };
	/// 컨텐츠가 들어갈  박스
	Gtk::Box contents_box_{ Gtk::ORIENTATION_HORIZONTAL };
	/// 종료 버튼을 적절한 크기로 윈도우에 추가하기 위한 박스
	Gtk::Box quit_box_{ Gtk::ORIENTATION_HORIZONTAL };
	
	/// 상단 타이틀 라벨
	Gtk::Label subtitle_{ kTitle };

	/// 버튼들이 들어간 박스
	ButtonBox button_box_;
	/// 텍스트 뷰가 들어간 박스
	TextWindow text_window_;

	/// 종료 버튼
	Gtk::Button quit_button_{ kQuitButtonText };
};

#endif

