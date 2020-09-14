/**
 * \file		proc_search_dialog.h
 * 
 * \brief		Proc 검색 다이얼로그
 * 
 * \date		2020.09.14.
 * 
 * \author		swma (swma@markany.com)
 * 
 * \copyleft	MarkAny Inc. 2020.
 */
#ifndef __SEARCH_DIALOG_H__
#define __SEARCH_DIALOG_H__

#include <memory>

#include <glibmm/refptr.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textview.h>

#include "agent_window.h"

class AgentWindow;

class ProcSearchDialog : public Gtk::Dialog {
public:
	/**
	 * @brief	Proc 검색 다이얼로그 객체 팩토리 생성
	 * 
	 * @return	std::unique_ptr< ProcSearchDialog >	다이얼로그의 포인터
	 */
	static std::unique_ptr< ProcSearchDialog > Create( );

	/**
	 * @brief	Proc 검색 다이얼로그 객체 소멸
	 */
	virtual ~ProcSearchDialog( ) { }

	ProcSearchDialog(
		const ProcSearchDialog&
		) = delete;
	ProcSearchDialog &operator=(
		const ProcSearchDialog &
		) = delete;

	ProcSearchDialog(
		ProcSearchDialog &&
		) = delete;
	ProcSearchDialog &operator=(
		ProcSearchDialog &&
		) = delete;
	
	/**
	 * @brief	종료 버튼을 누를 시 호출될 핸들러 함수 등록
	 * 
	 * @param	agent_window__		호출될 대상 AgentWindow 객체
	 * @param	handler_function__	호출될 객체 멤버 함수
	 */
	void AddQuitButtonHandler(
		AgentWindow&			agent_window__,
		AgentWindow::ProcDialogQuitButtonHandler handler_function__
		);

protected:
	/**
	 * @brief	검색 버튼을 클릭했을 경우 호출되는 핸들러
	 */
	void on_search_button_clicked( );

	/**
	 * @brief	사용자가 임의로 종료를 방지하기 위해 종료 요청 시 호출되는 핸들러
	 */
	bool on_delete_event(
		GdkEventAny*
		);

private:
	/**
	 * @brief	Proc 검색 다이얼로그 객체 생성 내부
	 */
	ProcSearchDialog( );

	/// 검색 버튼
	Gtk::Button search_button_{ "검색" };
	/// 종료 버튼
	Gtk::Button quit_button_{ "종료" };
	/// 커널 모듈 검색란
	Gtk::Entry kernel_module_input_;
	/// 커널 심볼 검색란
	Gtk::Entry kernel_symbol_input_;
	/// 검색 결과를 저장할 텍스트 버퍼
	Glib::RefPtr< Gtk::TextBuffer > search_result_buffer_;
	/// 텍스트 버퍼의 내용을 출력하는 텍스트 뷰
	Gtk::TextView search_result_view_;

	/// 각종 버튼이 들어갈 박스
	Gtk::Box button_box_;
	/// 커널 모듈 입력란에 대한 박스
	Gtk::Box kernel_module_box_;
	/// 커널 심볼 입력란에 대한 박스
	Gtk::Box kernel_symbol_box_;

	/// 텍스트 뷰가 들어갈 스크롤 가능 윈도우
	Gtk::ScrolledWindow search_result_window_;

	/// 커널 모듈 검색란 라벨
	Gtk::Label kernel_module_label_{ "Kernel module: " };
	/// 커널 심볼 검색란 라벨
	Gtk::Label kernel_symbol_label_{ "Kernel symbol: " };
};

#endif
