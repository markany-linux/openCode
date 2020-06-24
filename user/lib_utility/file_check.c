#include "file_check.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


/**
 * @brief	파일 확인을 위한 전체 요청 처리를 수행하는 메인 함수
 * 			대상의 종류(디렉터리/파일)와 관계 없이 권한 확인 동작을 수행
 * 
 * @param	pathname__	점검을 수행할 대상 경로
 * @param	flags__		점검할 권한
 * 
 * @return	대상이 존재 하고, 권한을 가지면 true, 아니면 false
 **/
static mild_bool check_access(
	mild_cstr					pathname__,
	mild_i32					flags__
	)
{
	/// check file exist first
	if( 0 != access( pathname__, F_OK ) )
		return mild_false;

	/// check request flags
	if( 0 != access( pathname__, flags__ ) )
		return mild_false;

	return mild_true;
}


/**
 * @brief	대상이 파일인 경우, 점검을 수행 하는 대리 함수
 * 
 * @param	pathname__	점검을 수행할 대상 파일의 경로
 * @param	flags__		점검할 권한
 * 
 * @return	일반 파일이고, 권한을 가지면 true, 아니면 false
 **/
static mild_bool check_file_access(
	mild_cstr					pathname__,
	mild_i32					flags__
	)
{
	if( mild_false == check_regular_filetype( pathname__ ) )
		return mild_false;
	
	return check_access( pathname__, flags__ );
}


mild_bool check_access_read(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_access( pathname__, R_OK );
}

mild_bool checkAccessRead(
	mild_cstr					pathname__
	)
{
	return check_access_read( pathname__ );
}


mild_bool check_access_write(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_access( pathname__, W_OK );
}

mild_bool checkAccessWrite(
	mild_cstr					pathname__
	)
{
	return check_access_write( pathname__ );
}


mild_bool check_access_rdwr(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_access( pathname__, R_OK | W_OK );
}

mild_bool checkAccessRdwr(
	mild_cstr					pathname__
	)
{
	return check_access_rdwr( pathname__ );
}


mild_bool check_access_executable(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_access( pathname__, X_OK );
}

mild_bool checkAccessExecutable(
	mild_cstr					pathname__
	)
{
	return check_access_executable( pathname__ );
}


mild_bool check_can_file_read(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_access( pathname__, R_OK );
}

mild_bool checkCanFileRead(
	mild_cstr					pathname__
	)
{
	return check_can_file_read( pathname__ );
}


mild_bool check_can_file_write(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_access( pathname__, W_OK );
}

mild_bool checkCanFileWrite(
	mild_cstr					pathname__
	)
{
	return check_can_file_write( pathname__ );
}


mild_bool check_can_file_rdwr(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_access( pathname__, R_OK | W_OK );
}

mild_bool checkCanFileRdwr(
	mild_cstr					pathname__
	)
{
	return check_can_file_rdwr( pathname__ );
}


mild_bool check_can_file_executable(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_access( pathname__, X_OK );
}

mild_bool checkCanFileExecutable(
	mild_cstr					pathname__
	)
{
	return check_can_file_executable( pathname__ );
}


mild_bool check_file_exist(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_access( pathname__, F_OK );
}

mild_bool checkFileExist(
	mild_cstr					pathname__
	)
{
	return check_file_exist( pathname__ );
}


mild_bool check_file_status(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	/// 1. check if target file exist
	if( mild_false == check_file_exist( pathname__ ) )
		return mild_false;

	/// 2. check target file is regular file
	if( mild_false == check_regular_filetype( pathname__ ))
		return mild_false;

	/// 3. check if can read and write target file
	if( mild_false == check_file_access( pathname__, R_OK | W_OK ) )
		return mild_false;

	return mild_true;
}

mild_bool checkFileStatus(
	mild_cstr					pathname__
	)
{
	return check_file_status( pathname__ );
}


/**
 * @brief	대상 경로의 파일 종류를 확인하고 반환
 * 			stat( )을 이용하여 확인할 대상 파일 종류
 * 
 * @param	pathname__	인할 대상 파일 경로 이름
 * @param	type__		확인할 파일 종류
 * 
 * @return	파일 존재 및 요청 타입이면 true, 아니면 false
 */
static mild_bool check_file_type(
	mild_cstr					pathname__,
	mild_u32					type__
	)
{
	struct stat st;

	if( mild_false == check_access( pathname__, F_OK ) )
		return mild_false;

	if( 0 != stat( pathname__, &st ) )
		return mild_false;
	
	if( type__ != ( st.st_mode & S_IFMT ) )
		return mild_false;

	return mild_true;
}


mild_bool check_regular_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFREG );
}

mild_bool checkRegularFiletype(
	mild_cstr					pathname__
	)
{
	return check_regular_filetype( pathname__ );
}


mild_bool check_socket_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFSOCK );
}

mild_bool checkSocketFiletype(
	mild_cstr					pathname__
	)
{
	return check_socket_filetype( pathname__ );
}


mild_bool check_symlink_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFLNK );
}

mild_bool checkSymlinkFiletype(
	mild_cstr					pathname__
	)
{
	return check_symlink_filetype( pathname__ );
}


mild_bool check_block_device_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFBLK );
}

mild_bool checkBlockDeviceFiletype(
	mild_cstr					pathname__
	)
{
	return check_block_device_filetype( pathname__ );
}


mild_bool check_directory_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFDIR );
}

mild_bool checkDirectoryFiletype(
	mild_cstr					pathname__
	)
{
	return check_directory_filetype( pathname__ );
}


mild_bool check_character_device_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFCHR );
}

mild_bool checkCharacterDeviceFiletype(
	mild_cstr					pathname__
	)
{
	return check_character_device_filetype( pathname__ );
}


mild_bool check_fifo_filetype(
	mild_cstr					pathname__
	)
{
	if( mild_null == pathname__ )
		return mild_false;

	return check_file_type( pathname__, S_IFIFO );
}

mild_bool checkFifoFiletype(
	mild_cstr					pathname__
	)
{
	return check_fifo_filetype( pathname__ );
}


mild_bool check_directory_exist(
	mild_cstr					pathname__
	)
{
	return check_access( pathname__, F_OK );
}

mild_bool checkDirectoryExist(
	mild_cstr					pathname__
	)
{
	return check_directory_exist( pathname__ );
}


mild_bool check_directory_permissions(
	mild_cstr					pathname__,
	mild_bool					read_check__,
	mild_bool					write_check__,
	mild_bool					exec_check__
	)
{
	mild_i32 flags = 0;

	if( mild_false != read_check__ )
		flags |= R_OK;

	if( mild_false != write_check__ )
		flags |= W_OK;

	if( mild_false != exec_check__ )
		flags |= X_OK;

	return check_access( pathname__, flags );
}

mild_bool checkDirectoryPermissions(
	mild_cstr					pathname__,
	mild_bool					read_check__,
	mild_bool					write_check__,
	mild_bool					exec_check__
	)
{
	return check_directory_permissions( pathname__, read_check__, write_check__, exec_check__ );
}
