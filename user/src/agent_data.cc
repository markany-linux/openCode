#include "agent_data.h"

#include <unistd.h>

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "common.h"
#include "lib_utility/interface/config_handler.h"
#include "lib_utility/interface/crc.h"
#include "lib_utility/interface/file_check.h"
#include "lib_utility/interface/proc_handler.h"
#include "lib_utility/interface/system_info.h"
#include "lib_utility/interface/time_handler.h"

namespace {

/**
 * @brief	string 객체에 문자열 format을 지정하여 저장
 * 
 * @param	destination__	format 처리 결과를 받을 string 객체
 * @param	format__		format 형식
 * @param	args__			format 형식에 들어갈 값들
 *
 * @return	size_t			formatting 된 문자열 길이 (destination__ 길이는 제외)
 */
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
	
	/// C String 형식의 버퍼 길이를 지정하기 위해 포매팅 후의 길이를 구함
	/// + 1은 '\0'을 추가한 길이를 적용하기 위함
	buffer_size = snprintf( nullptr, 0, format__, args__ ... ) + 1;
	if( 0 >= buffer_size )
		return buffer_size;
	
	/// 구해진 길이만큼 C String 버퍼 생성
	cstring_buffer.reset( new char[ buffer_size ] );
	if( !cstring_buffer )
		return 0;
	
	/// C String 버퍼에 내용 포매팅
	buffer_size = snprintf( cstring_buffer.get( ), buffer_size,
							format__, args__ ... ) + 1;
	if( 0 >= buffer_size )
		return buffer_size;
	
	/// 결과를 받을 string 객체에 포매팅 된 값이 들어있는 C String 형식의 결과값 복사
	destination__ = cstring_buffer.get( );
	return buffer_size;
}

/**
 * @brief	string 객체에 문자열 format을 이어 붙임
 * 
 * @param	destination__	format 처리 결과를 붙일 string 객체
 * @param	format__		format 형식
 * @param	args__			format 형식에 들어갈 값들
 *
 * @return	size_t			formatting 된 문자열 길이 (destination__ 길이는 제외)
 */
template< typename ... Args >
size_t string_append_format(
	std::string&				destination__,
	const char*					format__,
	Args ...					args__
	)
{
	std::string format_string;
	size_t format_size = 0;

	/// 먼저 임시 문자열 객체에 내용 포매팅
	format_size = string_format( format_string, format__, args__ ... );
	if( 0 == format_size )
		return 0;
	
	/// 결과를 붙일 string 객체에 포매팅 문자열을 붙임
	destination__ += format_string;
	return format_size;
}

/**
 * @brief	string 객체에 'Key [CRC: ...] = Value [CRC: ...]' 형식의 쌍을 이어 붙임
 * 
 * @param	destination__	format 처리 결과를 붙일 string 객체
 * @param	key__			키 문자열
 * @param	value__			값 문자열
 */
void AppendDataPairWithCRC(
	std::string&				destination__,
	const char* 				key__,
	const char*					value__
	)
{
	/// 포맷 형식 문자열 상수
	const char* format = "%s [CRC: %x] = %s [CRC: %x]\n";
	mild_custr key =
		reinterpret_cast< mild_custr >( key__ );
	mild_custr value =
		reinterpret_cast< mild_custr >( value__ );
	mild_u32 key_crc = 0;
	mild_u32 value_crc = 0;

	/// 키에 해당하는 문자열의 CRC값을 구함
	key_crc = getCRCValue( key, strlen( key__ ) );
	/// 값에 해당하는 문자열의 CRC값을 구함
	value_crc = getCRCValue( value, strlen( value__ ) );

	/// 미리 지정한 포맷 형식에 따라 CRC값을 포함한 키, 값을 포매팅 후 붙임
	string_append_format( destination__, format,
						  key__, key_crc,
						  value__, value_crc);
}

/**
 * @brief	string 객체에 'Key = Value' 형식의 쌍을 이어 붙임
 * 
 * @param	destination__	format 처리 결과를 붙일 string 객체
 * @param	key__			키 문자열
 * @param	value__			값 문자열
 */
void AppendDataPair(
	std::string&				destination__,
	const char*					key__,
	const char*					value__
	)
{
	string_append_format( destination__, "%s = %s\n", key__, value__ );
}

/**
 * @brief	openCode 커널 모듈에서 생성된 파일의 존재여부를 검사하고 파일 스트림으로 열음
 * 
 * @param	stream__	파일을 열게 될 대상 파일 스트림
 * @param	file__		커널 모듈에서 생성된 파일명(오직 경로를 제외한 파일명만)
 * @return	true		해당 파일이 존재하고 성공적으로 파일을 열었을 경우
 * @return	false		해당 파일이 존재하지 않거나 파일을 열지 못했을 경우
 */
bool OpenKernelModuleFile(
	std::fstream&				stream__,
	const char*					file__
	)
{
	const std::string data_dir =
			std::string( SYSFS_HOME ) + '/' + SYSFS_EXPORT_DIR;
	
	if( mild_false == checkDirectoryExist( data_dir.c_str( ) ) )
		return false;
	
	const std::string file_path = data_dir + '/' + file__;
	if( mild_false == checkCanFileRead( file_path.c_str( ) ) )
		return false;
	
	stream__.open( file_path, std::ios_base::in );
	if( !stream__.is_open( ) )
	{
		std::cout << "Failed to open kernel module file: " << file__ << '\n';
		return false;
	}

	return true;
}

/**
 * @brief	매크로로 만들어진 버전값을 각 필드로 나눠줌
 * 
 * @param	destination__	각 필드값을 담을 배열
 * @param	size__			`destination__`의 배열 크기
 * @param	version__		
 */
void DeserializeMaVersion(
	mild_u32*					destination__,
	size_t						size__,
	mild_u32					version__
	)
{
	assert( 0 < size__ );

	/// mild_u32 형식의 배열 사이즈이므로 실제 배열 갯수를 구함
	size__ /= sizeof( mild_u32 );

	/// 각 필드별로 값을 구함
	/// 배열 크기에 맞춰서 들어감
	destination__[ 0 ] = MA_GET_MAJOR_VERSION( version__ );
	if( 1 < size__ )
		destination__[ 1 ] = MA_GET_MINOR_VERSION( version__ );
	if( 2 < size__ )
		destination__[ 2 ] = MA_GET_PATCH_VERSION( version__ );
	if( 3 < size__ )
		destination__[ 3 ] = MA_GET_CUSTOM_VERSION( version__ );
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

	/// 설정 리스트 공간 할당 후 설정들을 가져옴
	config_create = createConfigList( &config_list_ );
	if( config_create)
		config_init_ = initConfigList( config_list_, config_file_path__.c_str( ) );
}

ConfigData::~ConfigData( )
{
	/// 만약 설정 리스트가 유효하고 설정을 가져온 적 있다면 모든 데이터를 지우고 리스트 제거
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

	if( !config_init_ )
		return "";
	
	std::string output;

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

NetlinkData::~NetlinkData( )
{
	/// Netlink 소켓 닫음
	if( -1 != fd_ )
	{
		close( fd_ );
		fd_ = -1;
	}

	/// Netlink 통신 버퍼 할당 해제
	if( netlink_message_ )
	{
		free( netlink_message_ );
		netlink_message_ = nullptr;
	}
}

bool NetlinkData::Init( )
{
	std::cout << "[+] NetlinkData::Init()\n";
	/// Netlink 헤더 + 데이터의 총 길이
	const size_t message_size = NLMSG_SPACE( sizeof( netlink_data_ ) );
	/// 현재 프로세스 ID
	const pid_t pid = getpid( );
	/// Netlink 통신 버퍼 할당
	auto* message_raw = ( struct nlmsghdr* )malloc( message_size );

	/// 각종 통신을 위한 구조체들을 초기화
	memset( &iov_, 0x00, sizeof( iov_ ) );
	memset( &netlink_data_, 0x00, sizeof( netlink_data_ ) );

	if( !message_raw )
	{
		printf( "Not enough memories\n" );
		return false;
	}
	
	/// 통신 버퍼 초기화
	memset( message_raw, 0x00, message_size );

	/// Netlink 소켓을 열음
	int fd = socket( PF_NETLINK, SOCK_RAW, NETLINK_PORT_NUMBER );
	if( -1 == fd )
	{
		std::cout << "Failed to open netlink socket.\n";
		free( message_raw );
		return false;
	}
	
	/// 바인딩 정보 기록
	struct sockaddr_nl bind_address;
	memset( &bind_address, 0x00, sizeof( bind_address ) );
	bind_address.nl_family = AF_NETLINK;
	bind_address.nl_pid = pid;

	/// Netlink 소켓에 현재 접속에 대한 바인딩
	auto* address_ptr = reinterpret_cast< struct sockaddr* >( &bind_address );
	if( 0 > bind( fd, address_ptr, sizeof( bind_address ) ) )
	{
		std::cout << "Failed to bind address.\n";
		free( message_raw );
		close( fd );
		return false;
	}

	/// 실패할 수 있는 초기화를 모두 마쳤으므로 객체 멤버에 값 저장
	fd_ = fd;
	netlink_message_ = message_raw;

	/// 통신할 대상 커널 주소 설정
	memset( &kernel_address_, 0x00, sizeof( kernel_address_ ) );
	kernel_address_.nl_family = AF_NETLINK;

	netlink_data_.pid = pid;

	std::cout << "[-] NetlinkData::Init()\n";
	return true;
}

const std::string NetlinkData::GetAll( )
{
	std::cout << "[+] NetlinkData::GetAll()\n";
	PNETLINK_DATA data = nullptr;
	std::string output;

	/// Netlink 통신을 통해 정보를 받을 수 있을 때까지 계속 받음
	while( Get( ) )
	{
		/// 헤더를 제외한 실제 데이터를 가리킴
		data = reinterpret_cast< PNETLINK_DATA >(
				NLMSG_DATA( netlink_message_ ) );
		if( !data )
		{
			std::cout << "Failed to read netlink message.\n";
			break;
		}

		/// 커널 모듈에서 전달받은 데이터 출력
		string_append_format( output, "pid = %d\n", data->pid );
		string_append_format( output, "uid = %d\n", data->uid );
		string_append_format( output, "pid = %d\n", data->pid );
		string_append_format( output, "fname = %s\n", data->fname );
		string_append_format( output, "task = %s\n", data->task );

		/// 만약 더 이상 받을 수 있는 데이터가 없으면 반복문 종료
		if( mild_false == data->remain )
			break;
		
		/// 아직 받을 데이터가 남아있기 때문에 읽기 쉽도록 다음 데이터를 위해 한 줄을 띄움
		output += '\n';
	}

	std::cout << "[-] NetlinkData::GetAll()\n";
	return output;
}

bool NetlinkData::Get( )
{
	std::cout << "[+] NetlinkData::Get()\n";
	ssize_t ret = 0;
	/// 현재 프로세스 ID
	const pid_t pid = getpid( );
	/// Netlink 헤더 + 데이터의 총 길이
	const size_t message_size = NLMSG_SPACE( sizeof( netlink_data_ ) );
	
	/// 통신 목적지 정보 초기화
	memset( &message_header_, 0x00, sizeof( message_header_ ) );

	/// 이전에 받은 데이터 초기화 및 값 지정
	memset( netlink_message_, 0x00, message_size );
	netlink_message_->nlmsg_len = message_size;
	netlink_message_->nlmsg_pid = pid;

	/// 보낼 메세지 헤더에 목적지 및 I/O 대상을 알림
	message_header_.msg_name = &kernel_address_;
	message_header_.msg_namelen = sizeof( kernel_address_ );
	message_header_.msg_iov = &iov_;
	message_header_.msg_iovlen = 1;

	/// I/O 대상 구조체 지정
	iov_.iov_base = netlink_message_;
	iov_.iov_len = netlink_message_->nlmsg_len;

	/// 메세지에 데이터를 복사
	auto* data_ptr = NLMSG_DATA( netlink_message_ );
	memcpy( data_ptr, &netlink_data_, sizeof( netlink_data_ ) );

	/// 만들어진 메세지를 커널 모듈에 전달
	ret = sendmsg( fd_, &message_header_, 0 );
	if( 0 > ret )
	{
		std::cout << "Failed to send netlink message.\n";
		return false;
	}
	
	/// 커널 모듈에게서 데이터를 받음
	ret = recvmsg( fd_, &message_header_, 0 );
	if( 0 > ret )
	{
		std::cout << "Failed to receive netlink message.\n";
		return false;
	}

	std::cout << "[-] NetlinkData::Get()\n";
	return true;
}

const std::string GetSystemInfo( )
{
	MADRM_LOCAL_SYSTEM system_info;

	/// 시스템 정보를 저장할 멤버변수 초기화
	memset( &system_info, 0x00, sizeof( system_info ) );

	/// 시스템 정보 가져오기
	if( !getLocalSystemInfo( &system_info ) )
		return "";
	
	std::string output;
	
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

const std::string GetProcessData(
	const std::string&			single_instance_path__
	)
{
	constexpr const char* kProcExecPathFormat = "/proc/%d/exe";
	constexpr int kPathLength = 64;
	char path[ kPathLength ] = { 0, };
	pid_t pid = getpid( );
	std::string output;

	/// 프로세스 경로를 담은 파일 경로를 문자열로 만듦
	snprintf( path, sizeof( path ), kProcExecPathFormat, pid );
	/// 문자열로 만들어진 경로에 대한 링크 정보를 읽어 실제 경로를 획득
	readlink( path, path, sizeof( path ) );

	AppendDataPair( output, "Current Executable path", path );
	AppendDataPair( output,
					"Single Instance file path",
					single_instance_path__.c_str( ) );
	return output;
}

const std::string GetProcData(
	const std::string&			kernel_module__,
	const std::string&			kernel_symbol__
	)
{
	std::string output;
	bool exist = false;

	if( kernel_module__.size( ) )
	{
		std::string key = "Kernel module \"" + kernel_module__ + "\"";

		/// 커널 모듈 존재 여부 확인
		exist = checkKernelModuleExist( kernel_module__.c_str( ) );
		if( exist )
			AppendDataPair( output, key.c_str( ), "Exist" );
		else
			AppendDataPair( output, key.c_str( ), "Not exist" );
	}

	if( kernel_symbol__.size( ) )
	{
		std::string key = "Kernel symbol \"" + kernel_symbol__ + "\"";

		/// 커널 심볼 존재 여부 확인
		exist = checkKernelSymbolExist( kernel_symbol__.c_str( ), nullptr );
		if( exist )
			AppendDataPair( output, key.c_str( ), "Exist" );
		else
			AppendDataPair( output, key.c_str( ), "Not exist" );
	}

	return output;
}

const std::string GetSysfsInfo( )
{
	std::fstream info;
	/// 커널 모듈에서 만든 info 파일 열기
	if( !OpenKernelModuleFile( info, SYSFS_INFO_FILE ) )
		return "";
	
	SYSFS_INFO info_data;
	memset( &info_data, 0x00, sizeof( info_data ) );
	/// info 파일을 sysfs 구조체 형식으로 읽음
	info.read( reinterpret_cast< char* >( &info_data ), sizeof( info_data ) );
	if( info.fail( ) && !info.eof( ) )
	{
		std::cout << "Failed to read netlink file: " SYSFS_INFO_FILE << '\n';
		return "";
	}
	
	std::string output;
	mild_u32 version_detail[ 4 ] = { 0, };

	DeserializeMaVersion( version_detail, sizeof( version_detail ),
						  info_data.sysfs_version );
	string_append_format( output,
						  "sysfs_version = %u.%u.%u.%u\n",
						  version_detail[ 0 ],
						  version_detail[ 1 ],
						  version_detail[ 2 ],
						  version_detail[ 3 ] );
	DeserializeMaVersion( version_detail, sizeof( version_detail ),
						  info_data.netlink_version );
	string_append_format( output,
						  "netlink_version = %u.%u.%u.%u\n",
						  version_detail[ 0 ],
						  version_detail[ 1 ],
						  version_detail[ 2 ],
						  version_detail[ 3 ] );
	string_append_format( output,
						  "netlink_load = %d\n",
						  static_cast< int >( info_data.netlink_load ) );
	string_append_format( output,
						  "netlink_port = %u", info_data.netlink_port );
	
	std::fstream version;
	/// 커널 모듈에서 만든 version 파일 열기
	if( !OpenKernelModuleFile( version, SYSFS_VERSION_FILE ) )
		return output;
	
	char version_data[ 32 ] = { 0, };
	/// version 파일 내용 읽음
	version.read( version_data, sizeof( version_data ) );
	if( version.fail( ) && !version.eof( ) )
	{
		std::cout << "Failed to read netlink file: " SYSFS_VERSION_FILE << '\n';
		return output;
	}
	
	/// version 파일에는 숫자가 저장돼 있으므로 부호없는 10진수 형태로 변환
	auto numeric_version =
			static_cast< mild_u32 >( strtoul( version_data, nullptr, 10 ) );
	
	memset( version_detail, 0x00, sizeof( version_detail ) );
	DeserializeMaVersion( version_detail, sizeof( version_detail ),
						  numeric_version );
	string_append_format( output, "\n\nversion = %u.%u.%u.%u",
						  version_detail[ 0 ],
						  version_detail[ 1 ],
						  version_detail[ 2 ],
						  version_detail[ 3 ] );
	return output;
}

} // namespace data {
