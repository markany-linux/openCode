#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <gtkmm/window.h>
#include <gtkmm/application.h>

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
		const std::vector<ButtonInfo>& button_list__,
		const Glib::RefPtr<Gtk::Application> app__
		);
	
	/**
	 * @brief	메인 윈도우 객체 소멸
	 **/
	virtual ~MainWindow( );

protected:
	/// 종료 버튼 텍스트 상수
	static constexpr const char* kQuitButtonText = "종료";

	/**
	 * @brief	메인 박스에 파생 위젯 attach
	 **/
	void AttachChildWidgets( );

	/**
	 * @brief	종료 버튼 생성
	 **/
	void AttachQuitButton( );

	/**
	 * @brief	사용자가 임의로 종료를 시도할 시 호출되는 핸들러
	 * 
	 * @param	any_event__	TODO: 설명 추가 필요
	 **/
	bool on_delete_event(
		GdkEventAny* any_event__
		);
	
	/**
	 * @brief	종료 버튼 클릭 이벤트 핸들러
	 **/
	void on_quit_button_clicked( );

	const Glib::RefPtr<Gtk::Application> app_;

	/// 가장 최상단의 박스
	Gtk::Box main_box_;
	/// 상단 라벨 박스
	Subtitle subtitle_;
	/// 버튼들이 들어간 박스
	ButtonBox button_box_;

	/// 종료 박스
	Gtk::Box quit_box_;
	/// 종료 버튼
	Gtk::Button quit_button_;
};

#endif
