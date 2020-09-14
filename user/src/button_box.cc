#include "button_box.h"

#include <iostream>
#include <vector>

#include <gtkmm/enums.h>

#include "agent_data.h"
#include "text_window.h"

const std::string ButtonBox::kConfigFilePath = "config.cfg";

AgentButton::AgentButton(
	AgentButtonType				type__,
	const std::string&			label__
	) : Gtk::Button( label__ ), type_( type__)
{	
}

ButtonBox::ButtonBox(
	TextWindow&					text_window__
	) : Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 ), text_window_( text_window__ )
{
	std::cout << "[+] ButtonBox::ButtonBox()\n";
	AddButton( AgentButtonType::kConfig, kConfigButtonLabel );
	AddButton( AgentButtonType::kSystem, kSystemButtonLabel );
	AddButton( AgentButtonType::kProcess, kProcessButtonLabel );
	AddButton( AgentButtonType::kProc, kProcButtonLabel );
	AddButton( AgentButtonType::kTime, kTimeButtonLabel );
	std::cout << "[-] ButtonBox::ButtonBox()\n";
}

ButtonBox::~ButtonBox( )
{
	std::cout << "ButtonBox::~ButtonBox()\n";
}

bool ButtonBox::AddButton(
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
				*this,
				&ButtonBox::on_button_clicked ), button->GetType( ) ) );

	pack_start( *button );

	buttons_.emplace_back( std::move( button ) );
	std::cout << "[-] ButtonBox::AddButton()\n";
	return true;
}

void ButtonBox::on_button_clicked(
	AgentButtonType				button_type__
	)
{
	std::cout << "[+] AgentMain::on_button_clicked()\n";
	switch( button_type__ )
	{
		case AgentButtonType::kConfig:
		{
			text_window_.ShowText( config_data_.GetConfigData( ) );
			break;
		}
		case AgentButtonType::kSystem:
		{
			text_window_.ShowText( data::GetSystemInfo( ) );
			break;
		}
		case AgentButtonType::kProcess:
			break;
		case AgentButtonType::kProc:
			break;
		case AgentButtonType::kTime:
		{
			text_window_.ShowText( data::GetTimeInfo( ) );
			break;
		}
	}
	std::cout << "[-] AgentMain::on_button_clicked()\n";
}
