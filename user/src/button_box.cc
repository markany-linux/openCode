#include "button_box.h"

#include <iostream>
#include <vector>

#include <gtkmm/enums.h>

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
	std::cout << "[+] ButtonBox::ButtonBox()\n";
	AddButton( agent_main__, AgentButtonType::kConfig, kConfigButtonLabel );
	AddButton( agent_main__, AgentButtonType::kSystem, kSystemButtonLabel );
	AddButton( agent_main__, AgentButtonType::kProcess, kProcessButtonLabel );
	AddButton( agent_main__, AgentButtonType::kProc, kProcButtonLabel );
	AddButton( agent_main__, AgentButtonType::kTime, kTimeButtonLabel );
	std::cout << "[-] ButtonBox::ButtonBox()\n";
}

ButtonBox::~ButtonBox( )
{
	std::cout << "ButtonBox::~ButtonBox()\n";
}

bool ButtonBox::AddButton(
	AgentMain*					agent_main__,
	AgentButtonType				type__,
	const std::string			label__
	)
{
	std::cout << "[+] ButtonBox::AddButton()\n";
	auto button = std::make_unique<AgentButton>( type__, label__ );
	if( !button )
	{
		std::cout << "Failed to create button.\n";
		return false;
	}

	button->signal_clicked( ).connect(
		sigc::bind(
			sigc::mem_fun(
				agent_main__,
				&AgentMain::on_button_clicked ), button->GetType( ) ) );

	pack_start( *button );

	buttons_.emplace_back( std::move( button ) );
	std::cout << "[-] ButtonBox::AddButton()\n";
	return true;
}

