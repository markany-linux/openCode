/**
 * \file		agent_data.h
 *
 * \brief		에이전트의 각종 정보들을 얻고,
 				사용자가 읽을 수 있는 문자열로 변환해주는 기능 집합
 *
 * \date		2020.09.11.
 *
 * \author		swma (swma@markany.com)
 * 
 * \copyleft	MarkAny Inc. 2020.
 */

#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <linux/netlink.h>
#include <sys/socket.h>

#include <memory>
#include <string>
#include <vector>

extern "C" {

#include "lib_utility/interface/config_handler.h"
#include "lib_utility/interface/system_info.h"

}

class AgentMain;

namespace data {

class ConfigData
{
public:
	/**
	 * @brief	설정 파일에서 데이터를 가져오는 객체 생성
	 *
	 * @param	config_file_path__	설정 파일 경로
	 **/
	ConfigData(
		const std::string&		config_file_path__
		);
	
	ConfigData(
		const ConfigData&
		) = delete;
	ConfigData& operator=(
		const ConfigData&
		) = delete;

	ConfigData(
		ConfigData&&
		) = delete;
	ConfigData& operator=(
		ConfigData&&
		) = delete;
	
	/**
	 * @brief	설정 파일에서 데이터를 가저오는 객체 소멸
	 */
	~ConfigData( );
	
	/**
	* @brief	설정 파일의 정보를 가져와서 문자열로 변환
	* 
	* @return	설정 파일에 있는 정보들을 읽을 수 있도록 변환된 문자열
	**/
	const std::string GetConfigData( ) const;

private:
	/// 설정 파일에서 특정 키에 대한 값을 읽을 때 값의 최대 길이 지정
	static constexpr int kConfigValueSize = 256;
	/// 설정 파일에서 읽어올 정보의 키들을 담은 벡터 상수
	static const std::vector< const char* > kConfigKeys;

	/// 설정 정보 리스트 포인터
	PCONFIG_LIST config_list_ = nullptr;

	/// 설정 파일을 정상적으로 읽어왔는지에 대한 상태
	bool config_init_ = false;
};

class NetlinkData
{
public:
	~NetlinkData( );
	bool Init( );
	const std::string GetAll( );

private:
	bool Get( );

	int fd_ = -1;
	struct sockaddr_nl kernel_address_;
	struct nlmsghdr* netlink_message_;
	NETLINK_DATA netlink_data_;
	struct iovec iov_;
	struct msghdr message_header_;
};

/**
* @brief	각종 시스템 정보를 가져와서 문자열로 변환
* 
* @return	시스템 정보들을 읽을 수 있도록 변환된 문자열
**/
const std::string GetSystemInfo( );

/**
* @brief	각종 시간 정보를 가져와서 문자열로 변환
* 
* @return	시간 정보들을 읽을 수 있도록 변환된 문자열
**/
const std::string GetTimeInfo( );

/**
 * @brief	프로세스 정보를 가져와서 문자열로 변환
 * 
 * @param	single_instance_path__	싱글 인스턴스로 사용되는 파일 경로
 *
 * @return	const std::string		프로세스 정보들을 읽을 수 있도록 변환된 문자열
 */
const std::string GetProcessData(
	const std::string&			single_instance_path__
	);

/**
 * @brief	Proc 정보를 가져와서 문자열로 변환
 * 
 * @param	kernel_module__		검색할 커널 모듈명
 * @param	kernel_symbol__		검색할 커널 심볼명
 *
 * @return	const std::string	Proc 정보들을 읽을 수 있도록 변환된 문자열
 */
const std::string GetProcData(
	const std::string&			kernel_module__,
	const std::string&			kernel_symbol__
	);

/**
 * @brief	sysfs 정보를 가져와서 문자열로 변환
 * 
 * @return	const std::string	sysfs 정보들을 읽을 수 있도록 변환된 문자열
 */
const std::string GetSysfsInfo( );

} // namespace data {

#endif
