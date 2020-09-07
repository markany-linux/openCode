#include "agent_data.h"

#include "lib_utility/gpl_list.h"
#include "lib_utility/interface/config_handler.h"

#include <string>

const std::vector< const char* > AgentData::kConfigKeys = {
	"SERVER_IP",
	"PORT"
};

AgentData::AgentData(
	AgentMain*					agent_main__,
	std::string&				config_file_path__
	) : agent_main_( agent_main__ )
{
	initConfigList( &config_list_, config_file_path__.c_str( ) );
	GetConfigData( );
}

const std::shared_ptr< std::string > AgentData::GetConfigData( )
{
	char value[ kConfigValueSize ] = { 0, };
	bool has_value = false;
	std::shared_ptr< std::string > output = std::make_shared< std::string >( );

	for( auto* key : kConfigKeys )
	{
		/// 문자열 항상 초기화
		value[ 0 ] = '\0';
		
		/// 키를 통하여 값을 요청
		has_value = getConfigListValue(
										&config_list_,
										key,
										value,
										sizeof( value ) );
		/// 해당 키를 설정에서 찾을 수 없거나 value 배열 크기가 모자란 경우
		if( mild_false == has_value )
			continue;

		/// 문자열이 버퍼를 넘어서지 못하도록 배열 끝을 항상 끊음
		value[ kConfigValueSize - 1 ] = '\0';

		/// 출력 형식:
		/// SERVER_IP = 192.168.1.1
		/// PORT = 7777
		//string_append( output.get( ), "%s = %s\n", key, value );
	}

	return output;
}

