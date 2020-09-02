#include "agent_main.h"

#include <iostream>

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
}

int AgentMain::Run( )
{
	return app_->run( );
}

void AgentMain::on_startup( )
{
	app_->add_window( agent_window_ );
}

bool AgentMain::on_delete_event(
	GdkEventAny*
	)
{
	/// 종료 명령 무시
	return true;
}

