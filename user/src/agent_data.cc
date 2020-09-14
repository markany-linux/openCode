#include "agent_data.h"

#include <string>
#include <cstring>

#include "common.h"
#include "lib_utility/interface/config_handler.h"
#include "lib_utility/interface/crc.h"
#include "lib_utility/interface/system_info.h"
#include "lib_utility/interface/time_handler.h"

namespace {

template< typename ... Args >
size_t string_format(
	std::string&				destination__,
	const char*					format__,
	Args ...					args__
	)
{
	int buffer_size = 0;
	std::unique_ptr< char[ ] > cstring_buffer = nullptr;

	if( !format__ )
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
	
	destination__ = cstring_buffer.get( );
	return buffer_size;
}

template< typename ... Args >
size_t string_append_format(
	std::string&				destination__,
	const char*					format__,
	Args ...					args__
	)
{
	std::string format_string;
	size_t format_size = 0;

	format_size = string_format( format_string, format__, args__ ... );
	if( 0 == format_size )
		return 0;
	
	destination__.append( format_string );
	return format_size;
}

void AppendDataPairWithCRC(
	std::string&				destination__,
	const char* 				key__,
	const char*					value__
	)
{
	const char* format = "%s [CRC: %x] = %s [CRC: %x]\n";
	mild_custr key =
		reinterpret_cast< mild_custr >( key__ );
	mild_custr value =
		reinterpret_cast< mild_custr >( value__ );
	mild_u32 key_crc = 0;
	mild_u32 value_crc = 0;

	key_crc = getCRCValue( key, strlen( key__ ) );
	value_crc = getCRCValue( value, strlen( value__ ) );

	string_append_format( destination__, format,
						  key__, key_crc,
						  value__, value_crc);
}

void AppendDataPair(
	std::string&				destination__,
	const char*					key__,
	const char*					value__
	)
{
	string_append_format( destination__, "%s = %s\n", key__, value__ );
}

} // namespace {

namespace data {

const std::vector< const char* > ConfigData::kConfigKeys = {
	"SERVER_IP",
	"PORT"
};

ConfigData::ConfigData(
	const std::string&			config_file_path__
	)
{
	bool config_create = false;

	config_create = createConfigList( &config_list_ );
	if( config_create)
		config_init_ = initConfigList( config_list_, config_file_path__.c_str( ) );
}

ConfigData::~ConfigData( )
{
	if( config_list_ )
	{
		if( config_init_ )
			cleanupConfigList( config_list_ );
		
		destroyConfigList( config_list_ );
	}
}

const std::string ConfigData::GetConfigData( ) const
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
		AppendDataPairWithCRC( output, key, value );
	}

	return output;
}

const std::string GetSystemInfo( )
{
	std::string output;
	MADRM_LOCAL_SYSTEM system_info;

	/// 시스템 정보를 저장할 멤버변수 초기화
	memset( &system_info, 0x00, sizeof( system_info ) );

	/// 시스템 정보 가져오기
	if( !getLocalSystemInfo( &system_info ) )
		return output;
	
	AppendDataPair( output, "distrib_id", system_info.distrib_id );

	AppendDataPair(
		output, "distrib_id_like", system_info.distrib_id_like );
	
	AppendDataPair(
		output, "distrib_name", system_info.distrib_name );
	
	AppendDataPair(
		output, "distrib_version", system_info.distrib_version );
	
	AppendDataPair(
		output, "distrib_version_id", system_info.distrib_version_id );
	
	AppendDataPair(
		output, "distrib_pretty", system_info.distrib_pretty );
	
	AppendDataPair(
		output, "local_ip", system_info.local_ip );
	
	AppendDataPair(
		output, "local_hostname", system_info.local_hostname );
	
	AppendDataPair(
		output, "local_nic", system_info.local_nic );	
	
	AppendDataPair(
		output, "kernel_version", system_info.kernel_version );										  												  						  						  						  

	return output;
}

const std::string GetTimeInfo( )
{
	mild_u64 current_time = 0;
	constexpr const size_t kTimeBufferLength = 64;
	char time_result[ kTimeBufferLength ] = { 0, };
	std::string output;

	if( getCurrentTimestamp( time_result ) )
		AppendDataPair( output, "Current Timestamp", time_result );
	
	if( getCurrentTimestampMn( time_result ) )
		AppendDataPair(
			output, "Current Timestamp Mn", time_result );
	
	if( getCurrentTimeReadable( time_result ) )
		AppendDataPair(
			output, "Current Time Readable", time_result );
	
	if( getCurrentDateReadable( time_result ) )
		AppendDataPair(
			output, "Current Date Readable", time_result );

	if( getCurrentDateTimeReadable( time_result ) )
		AppendDataPair(
			output, "Current Date Time Readable", time_result );

	if( getCurrentTime( &current_time ) )
	{
		getTimeReadable( current_time, time_result );
		AppendDataPair( output, "Time Readable", time_result );

		getDateReadable( current_time, time_result );
		AppendDataPair( output, "Date Readable", time_result );

		getDateTimeReadable( current_time, time_result, mild_true, mild_true );
		AppendDataPair( output, "Date Time Readable", time_result );
	}

	return output;
}

} // namespace data {
