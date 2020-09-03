#ifndef __BUTTON_BOX_H__
#define __BUTTON_BOX_H__

#include <memory>
#include <utility>

#include <gtkmm/box.h>
#include <gtkmm/button.h>

class AgentMain;

enum AgentButtonType
{
	kAgentButtonConfig,
	kAgentButtonSystem,
	kAgentButtonProcess,
	kAgentButtonProc,
	kAgentButtonTime
};

class AgentButton : public Gtk::Button
{
public:
	explicit AgentButton(
		AgentButtonType			type__,
		const std::string&		label__
		);
	~AgentButton( ) { }

	AgentButtonType GetType( )
	{
		return type_;
	}

private:
	AgentButtonType type_;
};

class ButtonBox : public Gtk::Box
{
public:
	/**
	 * @brief	버튼들을 가지는 박스 객체 생성
	 * 
	 * @param	contents_box__	상위 컨텐츠 박스
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

	virtual ~ButtonBox( );

	bool AddButton(
		AgentMain*				agent_main__,
		AgentButtonType			type__,
		const std::string		label__
		);

private:
	static constexpr const char* kConfigButtonLabel = "Config Info";
	static constexpr const char* kSystemButtonLabel = "System Info";
	static constexpr const char* kProcessButtonLabel = "Process Info";
	static constexpr const char* kProcButtonLabel = "Proc Info";
	static constexpr const char* kTimeButtonLabel = "Time Info";

	std::vector< std::unique_ptr< AgentButton > > buttons_;
};

#endif

