#include "agent_data.h"

#include "lib_utility/gpl_list.h"
#include "lib_utility/interface/config_handler.h"

#include <string>

AgentData::AgentData(
	AgentMain*					agent_main__,
	std::string&				config_file_path__,
	const ConfigKeyList&		key_list__
	) : agent_main_( agent_main__ )
{
	initConfigList( &config_list_, config_file_path__.c_str( ) );
	GetConfigData( key_list__ );
}

const DataString AgentData::GetConfigData(
	const ConfigKeyList&		key_list__
	)
{
	char value[ kConfigValueSize ] = { 0, };
	bool has_value = false;
	DataString output = std::make_shared< std::string >( );

	for( auto& key : key_list__ )
	{
		/// 문자열 항상 초기화
		value[ 0 ] = '\0';
		
		/// 키를 통하여 값을 요청
		has_value = getConfigListValue(
						&config_list_, key.c_str( ), value, sizeof( value ) );
		/// 해당 키를 설정에서 찾을 수 없거나 value 배열 크기가 모자란 경우
		if( mild_false == has_value )
			continue;

		/// 문자열이 버퍼를 넘어서지 못하도록 배열 끝을 항상 끊음
		value[ kConfigValueSize - 1 ] = '\0';

		/// 출력 형식:
		/// SERVER_IP = 192.168.1.1
		/// PORT = 7777
		output->append( key );
		output->append( " = " );
		output->append( value );
		output->append( "\n" );
	}

	return output;
}

