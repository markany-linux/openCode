#include "agent_main.h"

AgentMain::AgentMain( )
{
}

AgentMain::~AgentMain( )
{
}

int AgentMain::Run( )
{
	app_->signal_startup( ).connect(
		sigc::mem_fun( *this, &AgentMain::on_startup ) );

	return app_->run( );
}

void AgentMain::on_startup( )
{
	
}

