#ifndef __BUTTON_BOX_H__
#define __BUTTON_BOX_H__

#include <gtkmm/box.h>
#include <gtkmm/button.h>

class ContentsBox;

class ButtonBox : public Gtk::Box
{
public:
	/**
	 * @brief	버튼들을 가지는 박스 객체 생성
	 * 
	 * @param	info_list__	단일 또는 복수의 버튼 생성 정보들을 담은 벡터
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
		) = delete;
	ButtonBox& operator=(
		ButtonBox&&
		) = delete;

	virtual ~ButtonBox( );

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

	/// 컨텐츠 박스
	ContentsBox* contents_box_ = nullptr;

	Gtk::Button config_button_{ kConfigButtonLabel };
	Gtk::Button system_button_{ kSystemButtonLabel };
	Gtk::Button process_button_{ kProcessButtonLabel };
	Gtk::Button proc_button_{ kProcButtonLabel };
	Gtk::Button time_button_{ kTimeButtonLabel };
};

#endif

