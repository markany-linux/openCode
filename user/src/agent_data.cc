#include "agent_data.h"

#include "lib_utility/gpl_list.h"
#include "lib_utility/interface/config_handler.h"

#include <string>

const std::vector< const char* > AgentData::kConfigKeys = {
	"SERVER_IP",
	"PORT"
};

template< typename ... Args >
static size_t string_format(
	std::string*				destination__,
	const char*					format__,
	Args ...					args__
	)
{
	size_t buffer_size = 0;
	std::unique_ptr< char[ ] > cstring_buffer = nullptr;

	if( ( !destination__ ) || ( !format__ ) )
		return 0;
	
	buffer_size = snprintf( nullptr, 0, format__, args__ ... );
	if( 0 == buffer_size )
		return 0;
	
	cstring_buffer.reset( new char[ buffer_size + 1 ] );
	if( !cstring_buffer )
		return 0;
	
	buffer_size = snprintf( cstring_buffer.get( ), buffer_size,
							format__, args__ ... );
	if( 0 == buffer_size )
		return 0;
	
	*destination__ = cstring_buffer.get( );
	return buffer_size;
}

template< typename ... Args >
static size_t string_append_format(
	std::string*				destination__,
	const char*					format__,
	Args ...					args__
	)
{
	std::string format_string;
	size_t format_size = 0;

	format_size = string_format( destination__, format__, args__ ... );
	if( 0 == format_size )
		return 0;
	
	destination__->append( format_string );
	return format_size;
}

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
		string_append_format( output.get( ),
							  "%s = %s\n", key, value );
	}

	return output;
}

