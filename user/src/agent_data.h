/**
 * \file		agent_data.h
 *
 * \brief		에이전트의 각종 정보들을 얻고,
 				사용자가 읽을 수 있는 문자열로 변환해주는 클래스 선언
 *
 * \date		2020.09.11.
 *
 * \author		swma (swma@markany.com)
 * 
 * \copyleft	MarkAny Inc. 2020.
 */

#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <memory>
#include <string>
#include <vector>

#include "lib_utility/interface/config_handler.h"
#include "lib_utility/interface/system_info.h"

class AgentMain;

class AgentData
{
public:
	/**
	 * @brief	에이전트에서 각종 데이터를 가져오는 객체 생성
	 *
	 * @param	agent_main__		에이전트 메인 객체
	 * @param	config_file_path__	설정 파일 경로
	 * @param	key_list__			설정 파일에서 읽어올 키 리스트
	 **/
	AgentData(
		const std::string&		config_file_path__
		);

	AgentData(
		const AgentData&
		) = delete;
	AgentData& operator=(
		const AgentData&
		) = delete;

	AgentData(
		AgentData&&
		) = delete;
	AgentData& operator=(
		AgentData&&
		) = delete;

	/**
	 * @brief	에이전트 객체 소멸
	 **/
	~AgentData( );

	/**
	 * @brief	설정 파일의 정보를 가져와서 문자열로 변환
	 * 
	 * @return	설정 파일에 있는 정보들을 읽을 수 있도록 변환된 문자열
	 **/
	const std::string GetConfigData( );

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

private:
	/// 설정 파일에서 특정 키에 대한 값을 읽을 때 값의 최대 길이 지정
	static constexpr int kConfigValueSize = 256;
	static const std::vector< const char* > kConfigKeys;

	PCONFIG_LIST config_list_ = nullptr;
	MADRM_LOCAL_SYSTEM system_info_;

	bool config_init_ = false;
};

#endif

