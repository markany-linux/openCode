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

class AgentMain;

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
	 * @param	agent_main__	상위 컨텐츠 박스
	 **/
	ButtonBox(
		AgentMain*				agent_main__
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
	 * @param	agent_main__	클릭 시그널을 받을 에이전트 메인 객체
	 * @param	type__			생성될 버튼의 종류
	 * @param	label__			생성될 버튼의 라벨
	 * @return	true			버튼 생성 및 클릭 시그널 핸들러 등록 성공
	 * @return	false			버튼 생성이나 클릭 시그널 핸들러 등록 실패
	 */
	bool AddButton(
		AgentMain*				agent_main__,
		AgentButtonType			type__,
		const std::string		label__
		);

private:
	/// Config 버튼 라벨
	static constexpr const char* kConfigButtonLabel = "Config Info";
	/// System 버튼 라벨
	static constexpr const char* kSystemButtonLabel = "System Info";
	/// Process 버튼 라벨
	static constexpr const char* kProcessButtonLabel = "Process Info";
	/// Proc 버튼 라벨
	static constexpr const char* kProcButtonLabel = "Proc Info";
	/// Time 버튼 라벨
	static constexpr const char* kTimeButtonLabel = "Time Info";

	/// 동적으로 생성된 버튼들을 담는 벡터
	std::vector< std::unique_ptr< AgentButton > > buttons_;
};

#endif

