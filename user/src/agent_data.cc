#include "agent_data.h"

#include "lib_utility/gpl_list.h"
#include "lib_utility/interface/config_handler.h"

#include <string>

AgentData::AgentData(
	AgentMain*					agent_main__,
	std::string&				config_file_path__
	) : agent_main_( agent_main__ )
{
	initConfigList( &config_list_, config_file_path__.c_str( ) );
}

void AgentData::GetConfigData( )
{
	PAGENT_CONFIG config = nullptr;

	list_for_each( config, config_list_.list_head )
	{
	}
}

