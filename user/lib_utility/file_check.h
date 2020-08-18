/**
 * \file	file_check.h
 *
 * \brief	file check if exist, or access permission and etc...
 *
 * \date	2020.05.26.
 *
 * \author	wikim (wikim@markany.com)
 *
 * \copyleft MarkAny Inc. 2020.
 */
#ifndef __LIB_UTILITY__FILE_CHECK_H__
#define __LIB_UTILITY__FILE_CHECK_H__


#include "common.h"


/**
 * @brief	대상에 대한 읽기 권한을 확인
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_access_read(
	mild_cstr					pathname__
	);


/**
 * @brief	대상에 대한 쓰기 권한을 확인
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_access_write(
	mild_cstr					pathname__
	);


/**
 * @brief	대상에 대한 읽기/쓰기 권한을 확인
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_access_read_write(
	mild_cstr					pathname__
	);


/**
 * @brief	대상의 실행 권한을 확인
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_access_executable(
	mild_cstr					pathname__
	);


/**
 * @brief	대상의 읽기/쓰기/실행 권한을 확인
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, 권한이 존재하면 true, 아니면 false
 */
mild_bool check_access_rwx(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 파일의 읽기 권한을 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상 파일이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_can_file_read(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 파일의 쓰기 권한을 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상 파일이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_can_file_write(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 파일의 읽기/쓰기 권한을 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상 파일이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_can_file_readwrite(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 파일의 실행 권한을 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상 파일이 존재하고, 권한이 존재하면 true, 아니면 false
 **/
mild_bool check_can_file_executable(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 파일의 읽기/쓰기/실행 권한을 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상 파일이 존재하고, 권한이 존재하면 true, 아니면 false
 */
mild_bool check_can_file_rwx(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 파일이 존재 하는지 여부를 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	존재하면 true, 존재 하지 않으면 false
 **/
mild_bool check_file_exist(
	mild_cstr					pathname__
	);


/**
 * @brief	다음의 정보를 확인하고, 결과를 반환
 * 			- 대상 파일의 존재 여부 확인
 * 			- 대상이 일판 파일인지 여부 확인
 * 			- 요청 사용자가 파일에 대한 읽기/쓰기 권한을 갖는지 확인
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	존재하면 true, 존재 하지 않으면 false
 **/
mild_bool check_file_status(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 일반 파일인지 여부를 반환
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상이 존재하고, 일반 파일이면 true, 아니면 false
 **/
mild_bool check_regular_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 소켓(UDS)인지 여부를 반환
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상이 존재하고, 소켓이면 true, 아니면 false
 */
mild_bool check_socket_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 심볼릭 링크인지 여부를 반환
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상이 존재하고, 심볼릭 링크이면 true, 아니면 false
 */
mild_bool check_symlink_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 블록 디바이스 파일인지 여부를 반환
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상이 존재하고, 블록 디바이스 파일이면 true, 아니면 false
 */
mild_bool check_block_device_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 디렉터리인지 여부를 반환
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, 디렉터리면 true, 아니면 false
 */
mild_bool check_directory_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 문자 디바이스 파일인지 여부를 반환
 * 
 * @param	pathname__	확인할 대상 파일 경로명
 * 
 * @return	대상이 존재하고, 문자 디바이스 파일이면 true, 아니면 false
 */
mild_bool check_charater_device_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	대상 경로 파일이 FIFO 여부를 반환
 * 
 * @param	pathname__	확인할 대상 경로명
 * 
 * @return	대상이 존재하고, FIFO 라면 true, 아니면 false
 */
mild_bool check_fifo_filetype(
	mild_cstr					pathname__
	);


/**
 * @brief	디렉터리 존재 여부를 확인하고 반환
 * 
 * @param	pathname__	확인할 경로
 * 
 * @return	디렉터리 존재 시 true, 부재 시 false
 */
mild_bool check_directory_exist(
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
mild_bool check_directory_permissions(
	mild_cstr					pathname__,
	mild_bool					read_check__,
	mild_bool					write_check__,
	mild_bool					exec_check__
	)


#endif	// #ifndef __LIB_UTILITY__FILE_CHECK_H__

