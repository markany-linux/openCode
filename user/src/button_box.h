#ifndef __BUTTON_BOX_H__
#define __BUTTON_BOX_H__

#include <memory>
#include <utility>

#include <gtkmm/box.h>
#include <gtkmm/button.h>

class ContentsBox;

enum AgentButtonType
{
	kAgentButtonConfig,
	kAgentButtonSystem,
	kAgentButtonProcess,
	kAgentButtonProc,
	kAgentButtonTime
};

class AgentButton
{
public:
	explicit AgentButton(
		const std::string label__
		);
	~AgentButton( ) { }

private:
	AgentButtonType type_;
	Gtk::Button button_;
};

class ButtonBox : public Gtk::Box
{
public:
	/**
	 * @brief	버튼들을 가지는 박스 객체 생성
	 * 
	 * @param	contents_box__	상위 컨텐츠 박스
	 **/
	ButtonBox( );

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

	void AttachButtonsToSignal( );

private:
	/**
	 * @brief	버튼 클릭 이벤트가 발생됐을 때 호출되는 핸들러
	 * 
	 * @param
	 **/
	void on_button_clicked(
		Gtk::Button* button__
		);
	
	static constexpr const char* kConfigButtonLabel = "Config Info";
	static constexpr const char* kSystemButtonLabel = "System Info";
	static constexpr const char* kProcessButtonLabel = "Process Info";
	static constexpr const char* kProcButtonLabel = "Proc Info";
	static constexpr const char* kTimeButtonLabel = "Time Info";

	std::vector<std::unique_ptr<AgentButton>> buttons_;
};

#endif

