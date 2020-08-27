#ifndef __SUBTITLE_BOX_H__
#define __SUBTITLE_BOX_H__

#include <string>
#include <gtkmm/box.h>
#include <gtkmm/label.h>

class Subtitle : public Gtk::Box
{
public:
	/**
	 * @brief	상단 라벨 박스 생성
	 * 
	 * @param	text__	라벨 텍스트
	 **/
	explicit Subtitle(
		const std::string& text__
		);
	
	virtual ~Subtitle( );

protected:
	/// 실제 라벨 객체
	Gtk::Label label_;

private:
	Subtitle( ) = delete;
	Subtitle(
		Subtitle&
		) = delete;
	Subtitle(
		const Subtitle&
		) = delete;
	Subtitle(
		const Subtitle&&
		) = delete;
};

#endif
