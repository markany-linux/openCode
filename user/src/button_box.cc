#include "button_box.h"

#include <iostream>
#include <vector>

#include "contents_box.h"

AgentButton::AgentButton(
	const std::string label__
	) : button_( label__ )
{
}

ButtonBox::ButtonBox( )
		: Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 )
{
}

ButtonBox::~ButtonBox( )
{
}

void ButtonBox::on_button_clicked(
	Gtk::Button* button__
	)
{
	if( &config_button_ == button__ ) { }
	else if( &system_button_ == button__ ) { }
	else if( &process_button_ == button__ ) { }
	else if( &proc_button_ == button__ ) { }
	else { }
}

void ButtonBox::AttachButtonsToSignal( )
{
	std::vector<Gtk::Button*> buttons;

	buttons.push_back( &config_button_ );
	buttons.push_back( &system_button_ );
	buttons.push_back( &process_button_ );
	buttons.push_back( &proc_button_ );
	buttons.push_back( &time_button_ );

	for( auto* button : buttons )
	{
		button->signal_clicked( ).connect(
				sigc::bind(
					sigc::mem_fun(
						*this, &ButtonBox::on_button_clicked ), button ) );
	}
}

