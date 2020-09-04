#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <memory>
#include <string>

#include "lib_utility/interface/config_handler.h"

class AgentMain;

using DataString = std::shared_ptr< std::string >;

class AgentData
{
public:
	/**
	 * @brief	에이전트에서 각종 데이터를 가져오는 객체 생성
	 **/
	AgentData(
		AgentMain*				agent_main__,
		std::string&			config_file_path__
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

	DataString GetConfigData( );

private:
	AgentMain* agent_main_ = nullptr;
	CONFIG_LIST config_list_;
};

#endif

