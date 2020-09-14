#include <iostream>
#include <tuple>

#include "agent_main.h"

int main(
	int							argc,
	char*						argv[ ]
)
{
	AgentMain agent;
	bool agent_init = false;

	if( 2 <= argc )
		agent_init = agent.Init( argv[ 1 ] );
	else
		agent_init = agent.Init( );
	
	if( !agent_init )
	{
		std::cout << "The Agent can running only once\n";
		return 0;
	}

	return agent.Run( );
}

