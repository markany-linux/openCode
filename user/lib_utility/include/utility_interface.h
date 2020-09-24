/**
 * \file    interface/lib_utility.h
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.08.18.
 *          2020.09.24. (modified by swma)
 * 
 * \author  wikim (wikim@markany.com)
 *          swma (swma@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
#define __LIB_UTILITY__UTILITY_INTERFACE_H__


#ifdef __cplusplus
#include <ctime>

extern "C" {
#else
#include <time.h>
#endif

#include "common.h"


///////////////////////////////////////////////////////////////////////////////
//
// utility_init.c 인터페이스 정의
//  * 현재(2020.06.24) 라이브러리 버전을 획득하는 인터페이스만 존재
//
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief	유틸리티 라이브러리 버전 반환
 * 
 * @return	라이브러리 버전
 */
extern mild_u32 getMaUtilityLibraryVersion( void );


///////////////////////////////////////////////////////////////////////////////
//
// config_handler.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   config 리스트 관리 구조체
 */
typedef struct config_list_info
{
	/// 리스트 관리를 위한 헤드
	void*						list_head;
	/// 리스트 동기화 제어를 위한 동기화 멤버
	void*						list_lock;
} CONFIG_LIST, *PCONFIG_LIST;


/**
 * @brief   설정 리스트 생성
 *
 * @param   list__  생성되는 리스트를 반환받을 변수
 */
extern mild_bool createConfigList(
	PCONFIG_LIST                *list__
	);


/**
 * @brief   설정 리스트 제거
 *
 * @param   list__  대상 리스트
 */
extern void destroyConfigList(
	PCONFIG_LIST                list__
	);

/**
 * @brief   리스트의 모든 노드와 리스트 제거
 *
 * @param   list__  대상 리스트
 */
extern void cleanupConfigList(
	PCONFIG_LIST                list__
	);


/**
 * @brief   획득된 리스트에서 특정 설정 정보 값을 요청
 * 
 * @param   label__ 획득하려는 설정 라벨
 * @param   value__ 설정 라벨의 값을 반환 받을 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  설정 존재 및 반환 성공 true, 존재하지 않음 false
 */
extern mild_bool getConfigListValue(
	PCONFIG_LIST                list__,
	mild_cstr                   label__,
	mild_str                    value__,
	mild_u32                    len__
	);


/**
 * @brief   설정 파일을 읽고, 파싱하여 리스트로 모든 정보를 획득하는 함수
 * 
 * @param   pathname__  설정 파일 경로
 * 
 * @return  파일 존재/읽어서 파싱이 모두 성공 true, 실패 false
 */
extern mild_bool initConfigList(
	PCONFIG_LIST                list__,
	mild_cstr                   pathname__
	);


/**
 * @brief   파일을 읽어 획득된 모든 설정 정보의 출력
 */
extern void dispConfigListValue(
	PCONFIG_LIST                list__
	);


/**
 * @brief   설정 라벨과 값을 리스트에 추가
 * 
 * @param   label__ 추가할 설정 라벨
 * @param   value__ 추가할 설정 값
 * 
 * @return  리스트 추가 성공 true, 실패 false
 */
extern mild_bool addConfigList(
	PCONFIG_LIST                list__,
	mild_str					label__,
	mild_str					value__
	);


///////////////////////////////////////////////////////////////////////////////
//
// crc.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   CRC 값 획득을 위한 메인 인터페이스
 *          * 내부적으로 update_crc( ) 호출로 획득
 * 
 * @param   buffer__    CRC 값 획득을 위한 버퍼
 * @param   len__       버퍼의 길이
 * 
 * @return  버퍼에서 획득된 CRC 값
 */
extern mild_u32 getCRCValue(
    mild_custr                  buffer__,
    mild_i32                    len__
    );


///////////////////////////////////////////////////////////////////////////////
//
// file_check.c/h 인터페이스 정의
//  * 현재 프로세스 권한으로 접근할 수 없는 객체의 경우 무조건 실패
//  * checkAccessXxxxx( ) 형식은 대상이 파일/디렉터리 등 모든 객체에 대한 확인
//  * checkCanFileXxxx( ) 형식은 대상이 파일인 경우에만 확인
//
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief   객체 존재 확인 및 읽기 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 객체 경로
 * 
 * @return  객체 존재 및 읽기 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkAccessRead(
	mild_cstr					pathname__
	);


/**
 * @brief   객체 존재 확인 및 쓰기 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 객체 경로
 * 
 * @return  객체 존재 및 쓰기 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkAccessWrite(
	mild_cstr					pathname__
	);


/**
 * @brief   객체 존재 확인 및 읽기/쓰기 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 객체 경로
 * 
 * @return  객체 존재 및 읽기/쓰기 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkAccessRdwr(
	mild_cstr					pathname__
	);


/**
 * @brief   객체 존재 확인 및 실행 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 객체 경로
 * 
 * @return  객체 존재 및 실행 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkAccessExecutable(
	mild_cstr					pathname__
	);


/**
 * @brief   객체에 대해 모든 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 객체 경로
 * 
 * @return  객체 존재 및 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkAccessRWX(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 읽기 권한 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 읽기 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkCanFileRead(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 쓰기 권한 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 쓰기 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkCanFileWrite(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 읽기/쓰기 권한 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 읽기/쓰기 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkCanFileReadWrite(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 실행 권한 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 실행 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkCanFileExecutable(
	mild_cstr					pathname__
	);


/**
 * @brief   파일에 모든 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 권한 존재 true, 부재 또는 권한 없음 false
 */
extern mild_bool checkCanFileRWX(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 true, 부재 false
 */
extern mild_bool checkFileExist(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 상태를 확인하고 반환
 *           1. 파일 존재 여부 확인
 *           2. 일반 파일 여부 확인
 *           3. 읽기 쓰기 권한 존재 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  일반 파일이며 존재하고 읽기/쓰기 권한 존재 true, 하나라도 없으면 false
 */
extern mild_bool checkFileStatus(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 및 일반 파일 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 일반 파일이면 true, 부재 또는 다른 형식의 파일 false
 */
extern mild_bool checkRegularFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 및 도메인 소켓 파일 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 도메인 소켓이면 true, 부재 또는 다른 형식의 파일 false
 */
extern mild_bool checkSocketFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 및 소프트 링크 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 소프트 링크이면 true, 부재 또는 다른 형식의 파일 false
 */
extern mild_bool checkSymlinkFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 및 블록 디바이스 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 블록 디바이스면 true, 부재 또는 다른 형식의 파일 false
 */
extern mild_bool checkBlockDeviceFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   디렉터리 존재 여부 확인
 * 
 * @param   pathname__  확인할 디렉터리 경로
 * 
 * @return  디렉터리 존재 true, 부재 false
 */
extern mild_bool checkDirectoryFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 및 캐릭터 디바이스 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 캐릭터 디바이스면 true, 부재 또는 다른 형식의 파일 false
 */
extern mild_bool checkCharacterDeviceFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   파일 존재 및 FIFO 파일 여부 확인
 * 
 * @param   pathname__  확인할 파일 경로
 * 
 * @return  파일 존재 및 FIFO 파일이면 true, 부재 또는 다른 형식의 파일 false
 */
extern mild_bool checkFifoFiletype(
	mild_cstr					pathname__
	);


/**
 * @brief   디렉터리 존재 여부 확인
 *          ! 경로는 마지막에 "/" 없이 전달되어야 정상적으로 확인 가능
 *           Ex) /home/work -> (O) , /home/work/ (X)
 * 
 * @param   pathname__  확인할 디렉터리 경로
 * 
 * @return  디렉터리 존재 true, 존재하지 않음 false
 */
extern mild_bool checkDirectoryExist(
	mild_cstr					pathname__
	);


/**
 * @brief   디렉터리의 권한 확인
 *          ! 존재하는 디렉터리에 대한 권한만 확인
 *          ! 디렉터리 존재 여부는 checkDirectoryExist( )로 먼저 확인
 * 
 * @param   pathname__      확인할 디렉터리 경로
 * @param   read_check__    읽기 권한 확인 여부
 * @param   write_check__   쓰기 권한 확인 여부
 * @param   exec_check__    실행 권한 확인 여부
 * 
 * @return  디렉터리의 요청 권한 존재 시 true, 부재 시 false
 */
extern mild_bool checkDirectoryPermissions(
	mild_cstr					pathname__,
	mild_bool					read_check__,
	mild_bool					write_check__,
	mild_bool					exec_check__
	);


///////////////////////////////////////////////////////////////////////////////
//
// malog_handler.c/h 인터페이스 정의
//  * 로그 파일 생성, 로그 기록 등의 작업을 수행
//  * 에이전트 출력 설정에 따라 dprint( )에서 호출하여 로그를 기록하는 형식
//  * dprint( )이외의 로그 기록 인터페이스는 존재하지 않음
//
///////////////////////////////////////////////////////////////////////////////


extern mild_bool initLogFile(
    mild_i32                    *fd__,
    mild_cstr                   pathname__,
    mild_cstr                   dir_name__
    );


extern mild_bool writeLogFile(
    mild_i32                    fd__,
    mild_cstr                   log__
    );


extern void closeLogFile(
    mild_i32                    *fd__
    );


///////////////////////////////////////////////////////////////////////////////
//
// proc_handler.c/h 인터페이스 정의
//  * "/proc/modules" 파일에서 특정 모듈 존재 여부 확인
//  * "/proc/kallsyms" 파일에서 특정 커널 심볼 존재 여부 확인 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   "/proc/modules" 파일에서 특정 모듈 존재 여부 확인
 *          Ex. "/proc/modules" 파일 내용의 구성
 *          모듈 이름 | 크기 | 참조 | 참조 모듈 리스트                  | 상태 | 주소
 *          bluetooth 544768 29 rfcomm,bnep,btusb,btrtl,btbcm,btintel, Live 0xffffffffc0f96000
 * 
 * @param	module_name__	찾고자 하는 모듈 이름
 * 
 * @return  모듈이 발견되는 경우 true, 발견되지 않는 경우 false
 */
extern mild_bool checkKernelModuleExist(
	mild_cstr					target__
	);


/**
 * @brief   "/proc/kallsyms" 파일에서 특정 커널 심볼 존재 여부 확인
 *          Ex. "/proc/kallsyms" 파일 내용의 구성
 *          주소          | 형식 | 심볼 이름
 *          ffffffff9ac515d0 T sys_open
 * 
 * @param	symbol__	찾고자 하는 심볼 이름
 * @param	addr__		주소를 얻고자 할때, 전달
 * 
 * @return  심볼이 존재할 경우 true, 존재하지 않는 경우 false
 */
extern mild_bool checkKernelSymbolExist(
	mild_cstr					symbol__,
	mild_u64					*addr__
	);


///////////////////////////////////////////////////////////////////////////////
//
// single_instance.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


extern mild_bool setupSingleInstance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    );


extern void cleanupSingleInstance(
    mild_i32                    *fd__,
    mild_cstr                   pathname__
    );


///////////////////////////////////////////////////////////////////////////////
//
// string_parser.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   버퍼에서 특정 문자열이 존재할 때, 시작 위치 변위 값을 반환
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  현재 위치에서 이동해야 할 변위. 없는 경우 -1
 */
extern mild_i32 getTargetStringOffset(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 문자열 시작 위치의 포인터를 찾아 반환
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  시작 위치 포인터, 찾지 못한 경우 NULL
 */
extern mild_str getTargetStringPtr(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에 문자열 존재 여부만을 확인하고 반환
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  문자열이 존재하면 true, 존재하지 않으면 false
 */
extern mild_bool checkTargetStringExist(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 단일 문자 시작 위치를 찾아 변위 값 반환
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  이동해야 할 변위. 없는 경우 -1
 */
extern mild_i32 getTargetCharOffset(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 단일 문자 시작 위치 포인터를 찾아 반환
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  문자 위치 포인터, 존재하지 않으면 NULL
 */
extern mild_str getTargetCharPtr(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에 단일 문자 존재 여부 반환
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  문자가 존재하면 true, 존재하지 않으면 false
 */
extern mild_bool checkTargetCharExist(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 다음 라인('\n')까지의 변위 값을 찾아 반환
 *          현재 위치에서 바로 다음 '\n' 까지 변위를 찾음
 * 
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  이동해야 할 변위. 없는 경우 -1
 */
extern mild_i32 getNextLineOffset(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 다음 라인 시작 위치 포인터를 찾아 반환
 *          현재 위치에서 바로 다음 '\n' 위치를 찾음
 * 
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  다음 라인 위치 포인터. 없는 경우 NULL
 */
extern mild_str getNextLinePtr(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 현재 라인의 시작 위치 변위 값 반환
 *          바로 이전 '\n' 값을 찾음
 *          ! 이전에 '\n'이 존재하지 않으면 포인터 예외 오류가 발생하므로 주의 !
 * 
 * @param   buf__   버퍼의 현재 위치
 * 
 * @return  바로 이전 '\n' 까지 변위 값
 */
extern mild_i32 getCurrentLineStartOffset(
    mild_cstr                   buf__
    );


/**
 * @brief   버퍼에서 현재 라인 시작 위치 포인터 반환
 * 
 * @param   buf__   버퍼의 현재 위치
 * 
 * @return  바로 이전 '\n' 위치 포인터
 */
extern mild_str getCurrentLineStartPtr(
    mild_cstr                   buf__
    );


/**
 * @brief   버퍼에서 다음 위치의 공백 위치 변위를 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * @param   len__   버퍼 길이
 * 
 * @return  다음 공백까지 변위. 존재하지 않으면 -1
 */
extern mild_i32 getNextSpaceOffset(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 다음 위치의 공백 위치 포인터 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * @param   len__   버퍼 길이
 * 
 * @return  다음 공백의 시작 위치 포인터. 존재하지 않으면 NULL
 */
extern mild_str getNextSpacePtr(
    mild_cstr                   buf__,
    mild_i32                    len__
    );


/**
 * @brief   버퍼에서 이전 위치의 공백 위치 변위를 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * 
 * @return  이전 공백까지의 변위
 */
extern mild_i32 getPreviousSpaceOffset(
    mild_cstr                   buf__
    );


/**
 * @brief   버퍼에서 이전 위치의 공백 위치 포인터 반환
 * 
 * @param   buf__   현재 버퍼 위치
 * 
 * @return  이전 공백 위치 포인터
 */
extern mild_str getPreviousSpacePtr(
    mild_cstr                   buf__
    );


/**
 * @brief	버퍼에서 첫 번째로 공백까지의 문자 개수를 반환
 * 			! 버퍼의 시작 위치가 공백인 경우, 0이 반환되므로 주의해야 함
 *          FIXME: getNextSpaceOffset( )으로 대체하면 제거해야 함
 * 
 * @param	str__	확인할 버퍼
 * 
 * @return	문자의 개수
 */
extern mild_u32 getSpacePos(
	mild_str					str__
    );


/**
 * @brief   다음 라인(\n)으로 현재 포인터를 이동시키는 함수
 * 
 * @param   ptr__   다음 라인으로 이동할 포인터
 * 
 * @return  다음 라인까지의 변위
 */
extern mild_i32 currentLineSkip(
    mild_str                    *ptr__
    );


///////////////////////////////////////////////////////////////////////////////
//
// system_info.c/h 인터페이스 정의
//  * 
//  * 
//  * 
//
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief   에이전트가 설치된 배포판 정보
 */
typedef struct linux_distribution_system_informations
{
    /// Distribution ID
    mild_i8                     distrib_id[ STRLEN_32 ];

    /// Distribution ID like
    mild_i8                     distrib_id_like[ STRLEN_32 ];

    /// Distribution Name
    mild_i8                     distrib_name[ STRLEN_32 ];

    /// Distribution Version
    mild_i8                     distrib_version[ STRLEN_64 ];

    /// Distribution Version ID
    mild_i8                     distrib_version_id[ STRLEN_64 ];

    /// Distribution Pretty Name
    mild_i8                     distrib_pretty[ STRLEN_64 ];

    /// local ip address
    mild_i8                     local_ip[ STRLEN_24 ];

    /// local hostname
    mild_i8                     local_hostname[ STRLEN_64 ];

    /// local network interface card
    mild_i8                     local_nic[ STRLEN_32 ];

    /// current kernel version
    mild_i8                     kernel_version[ STRLEN_32 ];

} MADRM_LOCAL_SYSTEM, *PMADRM_LOCAL_SYSTEM;


/**
 * @brief   시스템과 배포판에 대한 정보를 획득하여 반환
 * 
 * @param   system__    획득된 정보를 반환할 구조체
 * 
 * @return  모든 정보 획득 성공 true, 실패 false
 */
extern mild_bool getLocalSystemInfo(
    PMADRM_LOCAL_SYSTEM         system__
    );


/**
 * @brief   시간 측정을 위한 구조체
 */
typedef struct time_interval_info_for_check_performace
{
    /// 측정 시작 시간
    mild_long                   start;

    /// 측정 종료 시간
    mild_long                   end;

} TIME_INTERVAL, *PTIME_INTERVAL;


/**
 * @brief	코드 동작 시간 정보 처리를 위한 정보 구조체
 */
typedef struct app_execution_time_check_info
{
	/// 코드 동작 시간 측정을 위한 시작 시간
	clock_t						app_start;

	/// 코드 동작 시간 측정을 위한 종료 시간
	clock_t						app_end;

	/// 시작 시간 설정 여부
	mild_bool					set_app;

} APP_TIME, *PAPP_TIME;


/**
 * @brief   현재 타임 스템프 정보 획득 및 반환
 *          * 년월일시분초까지만 획득 -> 201903051822
 *          * 버퍼는 최소 STRLEN_24 이상. 아이디 없으면 24가 적당
 * 
 * @param   stamp__ 타임 스템프 반환 버퍼
 * 
 * @return  획득 및 반환 성공 true, 실패 false
 */
extern mild_bool getCurrentTimestamp(
	mild_str					stamp__
	);


/**
 * @brief   현재 타임 스템프 정보 획득 및 반환
 *          * 년월일시분초밀나 정보 획득 -> 2019030518236721
 * 			* 버퍼는 최소 STRLEN_24 이상. 아이디까지 계산하면 64가 적당
 * 
 * @param   stamp__ 타임 스템프 반환 버퍼
 * 
 * @return  획득 및 반환 성공 true, 실패 false
 */
extern mild_bool getCurrentTimestampMn(
	mild_str					stamp__
	);


/**
 * @brief	현재 시간 정보를 숫자 형태로 반환
 * 
 * @param	cur_time__	반환할 숫자 형태의 시간
 * 
 * @return	시간 획득 성공 true, 실패 false
 */
extern mild_bool getCurrentTime(
	mild_u64					*time__
	);


/**
 * @brief	인수의 시간 정보를 읽을 수 있는 형태로 변환 및 반환
 * 			인수에서 시간 정보만을 변환
 * 			! 버퍼는 10 바이트 이상을 전달해야 함
 * 
 * @param	time__	변환할 시간 값
 * @param	buf__	변환 정보를 반환할 버퍼
 */
extern void getTimeReadable(
	mild_u64					time__,
	mild_str					buf__
	);


/**
 * @brief	인수의 시간 정보를 읽을 수 있는 형태로 변환 및 반환
 * 			인수에서 날짜 정보만을 변환
 * 			! 버퍼는 10 바이트 이상을 전달해야 함
 * 
 * @param	time__	변화할 시간 값
 * @param	buf__	변환 정보를 반환할 버퍼
 */
extern void getDateReadable(
	mild_u64					time__,
	mild_str					buf__
	);


/**
 * @brief	인수의 시간 정보를 읽을 수 있는 형태로 변환 및 반환
 * 			인수에서 날짜/시간을 선택적으로 변환 가능
 * 			! 버퍼는 요청에 따라 전달해야 함
 * 
 * @param	current__	변환할 시간 값
 * @param	buf__		변환 정보를 반환할 버퍼
 * @param	date__		날짜 변환 및 반환 여부
 * @param	time__		시간 변환 및 반환 여부
 */
extern void getDateTimeReadable(
	mild_u64					current__,
	mild_str					buf__,
	mild_bool					date__,
	mild_bool					time__
	);


/**
 * @brief	현재 시간을 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool getCurrentTimeReadable(
	mild_str					buf__
	);


/**
 * @brief	오늘 날짜를 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool getCurrentDateReadable(
	mild_str					buf__
	);


/**
 * @brief	현재 날짜/시간을 읽을 수 있는 형태로 변환 및 반환
 * 
 * @param	buf__	반환할 버퍼
 * 
 * @return	시간 획득 및 변환 성공 true, 실패 false
 */
extern mild_bool getCurrentDateTimeReadable(
	mild_str					buf__
	);


/**
 * @brief	전달 시간을 표준 출력
 * 
 * @param	time__		출력할 시간
 * @param	linefeed__	시간 출력 후, 줄 바꿈 여부
 */
extern void dispTimeReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	);


/**
 * @brief	전달 날짜를 표준 출력
 * 
 * @param	time__		출력할 시간
 * @param	linefeed__	날짜 출력 후, 줄 바꿈 여부
 */
extern void dispDateReadable(
	mild_u64					time__,
	mild_bool					linefeed__
	);


/**
 * @brief	전달 시간의 날짜와 시간을 표준 출력
 * 
 * @param	time__	출력할 시간
 */
extern void dispDateTimeReadable(
	mild_u64					time__
	);


extern void setAppStartTime(
	PAPP_TIME					app_time__
	); 


extern mild_float setAppEndTime(
	PAPP_TIME					app_time__
	);


/**
 * @brief	시간 차이 측정 시작, 종료 시에 호출하는 함수
 * 			* 종료 시에는 획득된 정보를 기반으로 차이 값을 표준 출력
 * 
 * @param	label__	시간 측정 종료 시에 출력할 문자열. NULL 허용
 * @param	ti__	시간 구조체
 * @param	start__	측정 시작 여부
 */
extern void setTimeInterval(
    PAPP_TIME                   app_time__,
	mild_cstr					label__,
	mild_bool					start__
	);


#ifdef __cplusplus
} // extern "C" {
#endif


#endif  // #ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
