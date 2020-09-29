#include "button_box.h"

#include <iostream>
#include <vector>

#include <gtkmm/enums.h>

#include "agent_data.h"
#include "agent_window.h"
#include "text_window.h"

const std::string ButtonBox::kConfigFilePath = "config.cfg";

AgentButton::AgentButton(
	AgentButtonType				type__,
	const std::string&			label__
	) : Gtk::Button( label__ ), type_( type__)
{	
}

ButtonBox::ButtonBox(
	AgentWindow&				agent_window__
	) : Gtk::Box( Gtk::ORIENTATION_VERTICAL, 0 ),
		agent_window_( agent_window__ )
{
	std::cout << "[+] ButtonBox::ButtonBox()\n";
	AddButton( AgentButtonType::kConfig, kConfigButtonLabel );
	AddButton( AgentButtonType::kSystem, kSystemButtonLabel );
	AddButton( AgentButtonType::kProcess, kProcessButtonLabel );
	AddButton( AgentButtonType::kProc, kProcButtonLabel );
	AddButton( AgentButtonType::kTime, kTimeButtonLabel );
	AddButton( AgentButtonType::kSysfs, kSysfsButtonLabel );
	AddButton( AgentButtonType::kNetlink, kNetlinkButtonLabel );
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
	using namespace data;

	std::cout << "[+] AgentMain::on_button_clicked()\n";
	TextWindow& text_window = agent_window_.GetTextWindow( );

	switch( button_type__ )
	{
		case AgentButtonType::kConfig:
		{
			text_window.ShowText( config_data_.GetConfigData( ) );
			break;
		}

		case AgentButtonType::kSystem:
		{
			text_window.ShowText( GetSystemInfo( ) );
			break;
		}

		case AgentButtonType::kProcess:
		{
			text_window.ShowText(
				GetProcessData( agent_window_.GetSingleInstanceFilePath( ) ) );
			break;
		}

		case AgentButtonType::kProc:
		{
			agent_window_.ShowProcSearchDialog( );
			break;
		}
		
		case AgentButtonType::kTime:
		{
			text_window.ShowText( GetTimeInfo( ) );
			break;
		}

		case AgentButtonType::kSysfs:
		{
			text_window.ShowText( GetSysfsInfo( ) );
			break;
		}

		case AgentButtonType::kNetlink:
		{
			text_window.ShowText( netlink_data_.GetAll( ) );
			break;
		}
	}
	std::cout << "[-] AgentMain::on_button_clicked()\n";
}
