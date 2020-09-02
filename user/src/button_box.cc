#include "button_box.h"

#include <iostream>

#include "contents_box.h"

ButtonBox::ButtonBox(
	ContentsBox* contents_box__
	)
		: Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 ),
		  contents_box_( contents_box__)
{
}

ButtonBox::~ButtonBox( )
{
	std::cout << "ButtonBox::~ButtonBox()\n";
}

void ButtonBox::on_button_clicked(
	Gtk::Button* button__
	)
{
	contents_box_->text_window_.AddText( button__->get_label() );
}

