#include "button_box.h"

#include <iostream>
#include <vector>

#include "agent_main.h"

AgentButton::AgentButton(
	AgentButtonType				type__,
	const std::string&			label__
	) : Gtk::Button( label__ ), type_( type__)
{	
}

ButtonBox::ButtonBox(
	AgentMain*					agent_main__
	)
		: Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 )
{
	AddButton( agent_main__, kAgentButtonConfig, kConfigButtonLabel );
	AddButton( agent_main__, kAgentButtonSystem, kSystemButtonLabel );
	AddButton( agent_main__, kAgentButtonProcess, kProcessButtonLabel );
	AddButton( agent_main__, kAgentButtonProc, kProcButtonLabel );
	AddButton( agent_main__, kAgentButtonTime, kTimeButtonLabel );
}

ButtonBox::~ButtonBox( )
{
}

bool ButtonBox::AddButton(
	AgentMain*					agent_main__,
	AgentButtonType				type__,
	const std::string			label__
	)
{
	auto button = std::make_unique<AgentButton>( type__, label__ );
	if( !button )
		return false;

	button->signal_clicked( ).connect(
		sigc::bind(
			sigc::mem_fun(
				agent_main__,
				&AgentMain::on_button_clicked ), button->GetType( ) ) );

	buttons_.emplace_back( std::move( button ) );
	return true;
}

