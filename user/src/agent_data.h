#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <memory>
#include <string>
#include <vector>

#include "lib_utility/interface/config_handler.h"

class AgentMain;

using ConfigKeyList = std::vector< std::string >;
using DataString = std::shared_ptr< std::string >;

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
		AgentMain*				agent_main__,
		std::string&			config_file_path__,
		const ConfigKeyList&	key_list__
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
	 * @param	key_list__	키를 담은 리스트
	 * 
	 * @return	설정 파일에 있는 정보들을 읽을 수 있도록 변환된 문자열
	 **/
	const DataString GetConfigData(
		const ConfigKeyList&	key_list__
		);

private:
	/// 설정 파일에서 특정 키에 대한 값을 읽을 때 값의 최대 길이 지정
	static constexpr int kConfigValueSize = 256;

	AgentMain* agent_main_ = nullptr;
	CONFIG_LIST config_list_;
};

#endif

