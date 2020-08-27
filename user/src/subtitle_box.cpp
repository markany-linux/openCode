#include "subtitle_box.h"

#include <iostream>

Subtitle::Subtitle(
	const std::string& text__
	) : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL), label_(text__)
{
	std::cout << "[+] Subtitle::Subtitle()\n";
	pack_start(label_, Gtk::PACK_EXPAND_WIDGET);
	/// 사용자에게 보여주기
	show( );
	std::cout << "[-] Subtitle::Subtitle()\n";
}

Subtitle::~Subtitle( )
{
	std::cout << "Subtitle::~Subtitle()\n";
}
