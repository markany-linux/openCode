/**
 * \file		button_box.h
 * 
 * \brief		버튼들을 가지는 박스
 * 
 * \date		2020.09.11.
 * 
 * \author		swma (swma@markany.com)
 * 
 * \copyleft	MarkAny Inc. 2020.
 */
#ifndef __BUTTON_BOX_H__
#define __BUTTON_BOX_H__

#include <memory>
#include <utility>

#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include "agent_data.h"

class AgentWindow;
class ProcSearchDialog;

enum AgentButtonType
{
	/// Config 버튼 타입
	kConfig,
	/// System 버튼 타입
	kSystem,
	/// Process 버튼 타입
	kProcess,
	/// Proc 버튼 타입
	kProc,
	/// Time 버튼 타입
	kTime
};

class AgentButton : public Gtk::Button
{
public:
	AgentButton(
		AgentButtonType			type__,
		const std::string&		label__
		);
	~AgentButton( ) { }

	/**
	 * @brief	버튼의 종류를 구함
	 * 
	 * @return	AgentButtonType 형식의 버튼 종류값
	 */
	AgentButtonType GetType( )
	{
		return type_;
	}

private:
	/// 버튼 종류 지정
	AgentButtonType type_;
};

class ButtonBox : public Gtk::Box
{
public:
	/**
	 * @brief	버튼들을 가지는 박스 객체 생성
	 * 
	 * @param	text_window__	정보를 표시할 텍스트 윈도우
	 **/
	ButtonBox(
		AgentWindow&			agent_window__
		);

	ButtonBox(
		const ButtonBox&
		) = delete;
	ButtonBox& operator=(
		const ButtonBox&
		) = delete;

	ButtonBox(
		ButtonBox&&
		);
	ButtonBox& operator=(
		ButtonBox&&
		);

	/**
	 * @brief	버튼 박스 객체 소멸
	 * 
	 */
	virtual ~ButtonBox( );

	/**
	 * @brief	버튼을 생성하고 클릭 시그널에 대한 핸들러 등록
	 * 
	 * @param	type__			생성될 버튼의 종류
	 * @param	label__			생성될 버튼의 라벨
	 *
	 * @return	true			버튼 생성 및 클릭 시그널 핸들러 등록 성공
	 * @return	false			버튼 생성이나 클릭 시그널 핸들러 등록 실패
	 */
	bool AddButton(
		AgentButtonType			type__,
		const std::string		label__
		);

private:
	/// Config 버튼 라벨
	static constexpr const char* kConfigButtonLabel = "Config Info\n(With CRC)";
	/// System 버튼 라벨
	static constexpr const char* kSystemButtonLabel = "System Info";
	/// Process 버튼 라벨
	static constexpr const char* kProcessButtonLabel = "Process Info";
	/// Proc 버튼 라벨
	static constexpr const char* kProcButtonLabel = "Proc Info";
	/// Time 버튼 라벨
	static constexpr const char* kTimeButtonLabel = "Time Info";

	/// 설정 파일 경로
	static const std::string kConfigFilePath;

	void ShowProcSearchDialog( );

	/**
	 * @brief	버튼 박스에 등록된 버튼들 중 클릭된 것이 있을 경우 호출되는 핸들러
	 * 
	 * @param	button_type__	클릭된 버튼의 종류
	 */
	void on_button_clicked(
		AgentButtonType				button_type__
		);
	
	

	/// 동적으로 생성된 버튼들을 담는 벡터
	std::vector< std::unique_ptr< AgentButton > > buttons_;

	/// 설정 파일 정보를 제공해주는 객체
	data::ConfigData config_data_{ kConfigFilePath };

	/// 정보를 표시할 텍스트 윈도우 객체 포인터
	AgentWindow& agent_window_;
};

#endif

