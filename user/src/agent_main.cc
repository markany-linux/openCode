#include "agent_main.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "agent_data.h"
#include "button_box.h"
#include "lib_utility/interface/single_instance.h"

AgentMain::~AgentMain( )
{
	std::cout << "[+] AgentMain::~AgentMain()\n";
	app_->quit( );
	cleanupSingleInstance( &instance_, instance_path_.c_str( ) );
	std::cout << "[-] AgentMain::~AgentMain()\n";
}

int AgentMain::Run( )
{
	std::cout << "[+] AppMain::Run()\n";
	int ret = app_->run( );
	std::cout << "[-] AppMain::Run()\n";
	return ret;
}

bool AgentMain::Init(
	const char*					instance_path__
	)
{
	assert( instance_path__ && "Invalid instance path" );

	/// 중복 실행을 방지하기 위한 싱글 인스턴스 설정
	bool instance_setup = setupSingleInstance( &instance_, instance_path__ );
	if( !instance_setup )
		return false;
	
	/// 프로그램 종료 시 싱글 인스턴스를 해제하기 위해 경로 저장
	instance_path_ = instance_path__;
	
	/// 애플리케이션이 구동을 시작할 때에 대한 핸들러 등록
	app_->signal_startup( ).connect(
		sigc::mem_fun( *this, &AgentMain::on_startup ) );

	/// 사용자가 임의로 종료를 시도할 때에 대한 핸들러 등록
	agent_window_.signal_delete_event( )
		.connect( sigc::mem_fun( *this, &AgentMain::on_delete_event ) );
	
	return true;
}

bool AgentMain::Init( )
{
	return Init( kDefaultInstancePath );
}

void AgentMain::on_startup( )
{
	std::cout << "[+] AgentMain::on_startup()\n";
	if( instance_ )
	{
		app_->add_window( agent_window_ );
		agent_window_.show( );
	}
	std::cout << "[-] AgentMain::on_startup()\n";
}

bool AgentMain::on_delete_event(
	GdkEventAny*
	)
{
	/// 종료 명령 무시
	return true;
}
