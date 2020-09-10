#include "agent_main.h"

#include <iostream>

#include "button_box.h"

const std::string AgentMain::kConfigFilePath = "config.cfg";

AgentMain::AgentMain( )
{
	/// 애플리케이션이 구동을 시작할 때에 대한 핸들러 등록
	app_->signal_startup( ).connect(
		sigc::mem_fun( *this, &AgentMain::on_startup ) );

	/// 사용자가 임의로 종료를 시도할 때에 대한 핸들러 등록
	agent_window_.signal_delete_event( )
		.connect( sigc::mem_fun( *this, &AgentMain::on_delete_event ) );
}

AgentMain::~AgentMain( )
{
	app_->quit( );
}

int AgentMain::Run( )
{
	std::cout << "[+] AppMain::Run()\n";
	int ret = app_->run( );
	std::cout << "[-] AppMain::Run()\n";
	return ret;
}

void AgentMain::on_button_clicked(
	AgentButtonType				button_type__
	)
{
	std::cout << "[+] AgentMain::on_button_clicked()\n";
	switch( button_type__ )
	{
		case AgentButtonType::kConfig:
		{
			agent_window_.ShowText( agent_data_.GetConfigData( ) );
			break;
		}
		case AgentButtonType::kSystem:
		{
			agent_window_.ShowText( agent_data_.GetSystemInfo( ) );
			break;
		}
		case AgentButtonType::kProcess:
			break;
		case AgentButtonType::kProc:
			break;
		case AgentButtonType::kTime:
			break;
	}
	std::cout << "[-] AgentMain::on_button_clicked()\n";
}

void AgentMain::on_startup( )
{
	std::cout << "[+] AgentMain::on_startup()\n";
	app_->add_window( agent_window_ );
	agent_window_.show( );
	std::cout << "[-] AgentMain::on_startup()\n";
}

bool AgentMain::on_delete_event(
	GdkEventAny*
	)
{
	/// 종료 명령 무시
	return true;
}

