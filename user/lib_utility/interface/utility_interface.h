/**
 * \file    utility_interface.h
 * 
 * \brief   유틸리티 라이브러리 인터페이스 정의
 * 
 * \date    2020.06.22.
 * 
 * \author  wikim (wikim@markany.com)
 * 
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
#define __LIB_UTILITY__UTILITY_INTERFACE_H__


#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


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
// time_handler.c 인터페이스 정의
//  * 시간 정보 획득을 위한 인터페이스
//  * 문자열 변환 및 성능 측정을 위한 인터페이스
//
///////////////////////////////////////////////////////////////////////////////

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
 * @brief	시간 차이 측정 시작, 종료 시에 호출하는 함수
 * 			* 종료 시에는 획득된 정보를 기반으로 차이 값을 표준 출력
 * 
 * @param	label__	시간 측정 종료 시에 출력할 문자열. NULL 허용
 * @param	ti__	시간 구조체
 * @param	start__	측정 시작 여부
 */
extern void setTimeInterval(
	mild_cstr					label__,
	PTIME_INTERVAL				ti__,
	mild_bool					start__
	);


#ifdef __cplusplus
}
#endif


#endif  // #ifndef __LIB_UTILITY__UTILITY_INTERFACE_H__
