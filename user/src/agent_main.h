/**
 * \file		agent_main.h
 * 
 * \brief		에이전트 메인
 * 
 * \date		2020.09.11.
 * 
 * \author		swma (swma@markany.com)
 * 
 * \copyleft	MarkAny Inc. 2020.
 */
#ifndef __AGENT_MAIN_H__
#define __AGENT_MAIN_H__

#include "agent_window.h"
#include "button_box.h"

namespace Gtk {
class Application;
}

class AgentMain
{
public:
	/**
	 * @brief	에이전트 메인 객체 생성
	 * 
	 */
	AgentMain( ) { }
	/**
	 * @brief	에이전트 메인 객체 소멸
	 *			프로그램이 최종 종료될 때 호출됨
	 * 
	 */
	~AgentMain( );

	AgentMain(
		const AgentMain&
		) = delete;
	AgentMain& operator=(
		const AgentMain&
		) = delete;
	
	AgentMain(
		AgentMain&&
		) = delete;
	AgentMain& operator=(
		AgentMain&&
		) = delete;

	/**
	 * @brief	GUI 실행
	 * 
	 * @return	GUI가 최종적으로 정상종료 됐는 지에 대한 값
	 *			자세한 사항은 `Gtk::Application::run()` 참고
	 */
	int Run( );

	/**
	 * @brief	에이전트 메인 초기화
	 * 
	 * @param	instance_path__	싱글 인스턴스 역할을 할 파일 경로
	 * @return	true			초기화에 성공할 시
	 * @return	false			초기화에 실패할 시
	 */
	bool Init(
		const char*				instance_path__
		);
	/**
	 * @brief	에이전트 메인 초기화
	 *			싱글 인스턴스 역할을 하는 파일 경로는 기본값으로 설정
	 * 
	 * @return	true	초기화에 성공할 시
	 * @return	false	초기화에 실패할 시
	 */
	bool Init( );

private:
	/// GTK 애플리케이션 ID
	static constexpr const char* kAppIdentifier = "com.gnome.opencode";
	/// 싱글 인스턴스로 이용될 파일의 경로
	static constexpr const char* kDefaultInstancePath = "/tmp/openCode.pid";

	/**
	 * @brief	GTK 애플리케이션이 시작될 때 호출되는 핸들러
	 * 
	 */
	void on_startup( );

	/**
	 * @brief	애플리케이션을 임의로 종료를 시도할 때 호출되는 핸들러
	 * 
	 * @param	any_event__	`on_delete_event()` 기본 인자
	 */
	bool on_delete_event(
		GdkEventAny* any_event__
		);

	/// GTK 애플리케이션 메인
	Glib::RefPtr<Gtk::Application> app_ =
		Gtk::Application::create( kAppIdentifier );
	
	/// 에이전트 윈도우
	AgentWindow agent_window_{ instance_path_ };

	/// 싱글 인스턴스로 이용될 파일의 경로
	std::string instance_path_;
	/// 싱글 인스턴스 파일의 디스크립터
	int instance_ = 0;
};

#endif

