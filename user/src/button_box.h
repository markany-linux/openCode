#ifndef __BUTTON_BOX_H__
#define __BUTTON_BOX_H__

#include <vector>
#include <memory>
#include <gtkmm/box.h>
#include <gtkmm/button.h>

/**
 * @brief	버튼 생성 정보를 저장하는 객체
 */
struct ButtonInfo
{
	/// 버튼 안에 들어가는 텍스트
	std::string text;
};


class ButtonBox : public Gtk::Box
{
public:
	/**
	 * @brief	버튼들을 가지는 박스 객체 생성
	 * 
	 * @param	info_list__	단일 또는 복수의 버튼 생성 정보들을 담은 벡터
	 **/
	explicit ButtonBox(
		const std::vector<ButtonInfo>& info_list__
		);
	
	/**
	 * @brief ```AddButtons``` 실제 Button 객체들이 벡터에 push될 때 호출될 복사 생성자
	 **/
	explicit ButtonBox(
		const ButtonBox& object
	) = default;

	virtual ~ButtonBox( );

protected:
	/// 실제 Button 객체들이 저장되는 공간
	std::vector<std::unique_ptr<Gtk::Button>> buttons_;

private:
	ButtonBox(
		const ButtonBox&&
		) = delete;
	
	/**
	 * @brief	생성자에서 전달받은 버튼 정보들을 통해 실제 버튼 객체들을 만들고
	 * 			벡터에 담아줌.
	 * 
	 * @param	info_list__	단일 또는 복수의 버튼 생성 정보들을 담은 벡터
	 **/
	void AddButtons(
		const std::vector<ButtonInfo>& info_list__
		);
};

#endif
