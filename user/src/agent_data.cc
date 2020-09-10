#include "agent_data.h"

#include "lib_utility/interface/config_handler.h"

#include <string>
#include <cstring>

const std::vector< const char* > AgentData::kConfigKeys = {
	"SERVER_IP",
	"PORT"
};

AgentData::AgentData(
	const std::string&			config_file_path__
	)
{
	bool config_create = false;

	config_create = createConfigList( &config_list_ );
	if( config_create)
		config_init_ = initConfigList( config_list_, config_file_path__.c_str( ) );
}

AgentData::~AgentData()
{
	if( config_list_ )
	{
		if( config_init_ )
			cleanupConfigList( config_list_ );
		
		destroyConfigList( config_list_ );
	}
}

template< typename ... Args >
static size_t string_format(
	std::string*				destination__,
	const char*					format__,
	Args ...					args__
	)
{
	int buffer_size = 0;
	std::unique_ptr< char[ ] > cstring_buffer = nullptr;

	if( ( !destination__ ) || ( !format__ ) )
		return 0;
	
	/// + 1은 '\0'을 추가한 길이를 적용하기 위함
	buffer_size = snprintf( nullptr, 0, format__, args__ ... ) + 1;
	if( 0 >= buffer_size )
		return buffer_size;
	
	cstring_buffer.reset( new char[ buffer_size ] );
	if( !cstring_buffer )
		return 0;
	
	buffer_size = snprintf( cstring_buffer.get( ), buffer_size,
							format__, args__ ... ) + 1;
	if( 0 >= buffer_size )
		return buffer_size;
	
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

	format_size = string_format( &format_string, format__, args__ ... );
	if( 0 == format_size )
		return 0;
	
	destination__->append( format_string );
	return format_size;
}

const std::string AgentData::GetConfigData( )
{
	char value[ kConfigValueSize ] = { 0, };
	bool has_value = false;
	std::string output;

	if( !config_init_ )
		return output;

	for( auto* key : kConfigKeys )
	{
		/// 문자열 항상 초기화
		memset( value, 0x00, sizeof( value ) );
		
		/// 키를 통하여 값을 요청
		has_value = getConfigListValue(
										config_list_,
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
		string_append_format( &output,
							  "%s = %s\n", key, value );
	}

	return output;
}

const std::string AgentData::GetSystemInfo( )
{
	std::string output;

	/// 시스템 정보를 저장할 멤버변수 초기화
	memset( &system_info_, 0x00, sizeof( system_info_ ) );

	/// 시스템 정보 가져오기
	if( !getLocalSystemInfo( &system_info_ ) )
		return output;
	
	string_format( &output, "distrib_id = %s\n", system_info_.distrib_id );
	string_append_format( &output, "distrib_id_like = %s\n",
						  system_info_.distrib_id_like );
	string_append_format( &output, "distrib_name = %s\n",
						  system_info_.distrib_name );
	string_append_format( &output, "distrib_version = %s\n",
						  system_info_.distrib_version );
	string_append_format( &output, "distrib_version_id = %s\n",
						  system_info_.distrib_version_id );
	string_append_format( &output, "distrib_pretty = %s\n",
						  system_info_.distrib_pretty );
	string_append_format( &output, "local_ip = %s\n",
						  system_info_.local_ip );
	string_append_format( &output, "local_hostname = %s\n",
						  system_info_.local_hostname );
	string_append_format( &output, "local_nic = %s\n",
						  system_info_.local_nic );	
	string_append_format( &output, "kernel_version = %s\n",
						  system_info_.kernel_version );										  												  						  						  						  

	return output;
}
