#include "proc_handler.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "file_check.h"
#include "string_parser.h"


/**
 * @brief	전달된 버퍼에 전달된 문자열이 존재하는지 여부 확인
 * 			버퍼에서 특정 문자열의 존재 여부를 확인
 * 			문자열의 존재만을 정확하게 확인하고, 결과를 반환
 * 
 * @param	buf__			문자열이 존재하는지 확인할 버퍼
 * @param	len__			문자열 버퍼의 길이
 * @param	target_str__	확인할 문자열
 * @param	separator__		문자열의 대상 구분자
 * @param	ptr__			문자열이 존재하는 경우, 문자열 시작 위치를 반환
 * 
 * @return	확인 문자열이 존재하는 경우 true, 아니면 false
 */
static mild_bool check_string_in_buffer(
	mild_str					buf__,
	mild_i32					len__,
	mild_cstr					target_str__,
	mild_i8						separator__,
	mild_str					*ptr__
	)
{
	mild_i32 i = 0;
	mild_i32 j = 0;
	mild_i32 target_len = strlen( target_str__ );

	/// 전체 문자열에 대한 검사를 수행
	for( ; i < len__; i++ )
	{
		/// 확인 대상 문자열 길이만큼 현재 위치의 버퍼 확인
		for( j = 0; j < target_len; j++ )
		{
			/// 현재 위치부터 동일한 문자열이 존재하는지 확인
			if( *( buf__ + i + j ) != *( target_str__ + j ) )
				break;
		}

		/// 동일 문자열 뒤의 문자가 전달된 구분자와 동일 여부 확인
		if( ( target_len == j ) && ( separator__ == *( buf__ + i + j ) ) )
		{
			/// 위치 반환이 요청된 경우, 발견 위치를 반환
			if( mild_null != ptr__ )
				*ptr__ = buf__ + i;

			return mild_true;
		}
	}

	/// 전체 검색에서 해당 문자열을 찾지 못한 경우
	return mild_false;
}


/**
 * @brief	현재 라인의 시작 위치('\n' 다음 위치)까지의 이동 변위 계산
 * 
 * @param	str__	확인할 버퍼의 시작 위치
 * 
 * @return	시작 위치까지의 변위 값
 */
static mild_u32 get_line_start_offset(
	mild_str					str__
	)
{
	mild_u32 cnt = 0;

	while( '\n' != *( str__ - 1 ) )
	{
		str__--;
		cnt++;
	}

	return cnt;
}


/**
 * @brief	버퍼에서 주소 값을 변환하여 반환
 * 
 * @param	addr__	버퍼 시작 위치
 * 
 * @return	변환된 주소 값
 */
static mild_u64 get_ksyms_address(
	mild_str					addr__
	)
{
	mild_i8 buf[ STRLEN_24 ] = { 0, };

	memcpy( buf, addr__, get_space_pos( addr__ ) );

	return strtoull( buf, NULL, STRLEN_16 );
}


/**
 * @brief	파일을 읽어 대상 문자열의 존재 여부 확인
 * 
 * @param	fd__		대상 파일 디스크립터
 * @param	mod_name__	찾을 문자열
 * 
 * @return	문자열이 존재하면 true, 파일 처리 실패 또는 존재하지 않는 경우 false
 */
static mild_bool fread_find_string(
	mild_i32					fd__,
	mild_cstr					str_name__,
	mild_i8						separator__,
	mild_u64					*addr__
	)
{
	mild_i8 buf[ PROC_READ_LEN ] = { 0, };
	mild_i32 readlen = 0;
	mild_u32 offset = 0;
	mild_str pos = mild_null;

	do
	{
		/// * 대상 파일에서 한 페이지를 읽음
		/// * "/proc/modules" or "/proc/kallsyms" 파일을 읽으면, 요청 길이만큼 읽는 것이 아니라,
		/// 정상적으로 모든 내용을 읽어 들일 수 있는 마지막 라인 까지만 읽어서 반환 됨.
		/// Ex. 다음의 경우, module_a 라인만 정상적으로 읽혀짐
		/// ...
		/// module_a 16384 1 usb, Live 0xffffffffc08bc000 <- read position
 		/// module_b 16384 1 usb, Live 0xffffffffc081e000
		///                  ^
		///                  | (4096 위치)
		/// 다음 요청은 module_b부터 시작되도록 구성되어 있으므로 처리가 편함
		/// 따라서, 읽기에 실패하거나 읽은 길이가 0인지 확인으로 마지막 위치인지 확인 가능
		readlen = read( fd__, buf, PROC_READ_LEN );
		if( ( 0 == readlen ) || ( -1 == readlen ) )
			break;

		/// * 읽어들인 버퍼에 대상 문자열이 존재하는지 여부를 확인. 존재하면 즉시 반환
		if( mild_false != check_string_in_buffer( buf, readlen, str_name__, separator__, &pos ) )
		{
			/// 커널 심볼인 경우, 주소 획득을 위해 포인터를 넘기면 값으로 변환하여 반환
			///			포인터를 전달되지 않으면 단순 확인만 수행
			///			일반 사용자의 경우, 커널에서 해당 값을 읽을 수 없으므로, 관리자가 아니면 의미 없음
			if( mild_null != addr__ )
			{
				/// 심볼 위치의 라인 시작 위치 변위 값을 획득
				/// Ex. 버퍼에서 주소 값의 시작 위치까지의 길이를 계산
				/// ffffffff9ac51350 T do_sys_open
				/// ffffffff9ac515d0 T SyS_open
				/// ffffffff9ac515d0 T sys_open
				/// ^                  ^
				/// | (줄의 시작 위치)  | (현재 위치)
				/// -------------------  (변위 계산으로 시작 위치 획득)
				offset = get_line_start_offset( pos );
				/// 해당 위치부터 주소 값을 문자에서 숫자로 변환하여 획득
				/// Ex. ffffffff9ac515d0 T sys_open
				///     ^              ^
				///     | (요청 위치)   | (주소 값 위치)
				*addr__ = get_ksyms_address( pos - offset );
			}

			/// 요청 문자열 존재를 반환
			return mild_true;
		}

		/// 읽어 들인 버퍼를 초기화.
		memset( buf, 0x00, PROC_READ_LEN );

	} while( mild_true );

	return mild_false;
}


mild_bool check_kernel_module_exist(
	mild_cstr					target_str__
	)
{
	mild_i32 fd = 0;
	mild_bool res = mild_false;

	if( mild_null == target_str__ )
		return mild_false;

	/// check if "/proc/modules" file exist with regular file type
	if( mild_false == check_regular_filetype( PROC_MODULE_FILE ) )
		return mild_false;

	/// open "/proc/modules" file
	fd = open( PROC_MODULE_FILE, O_RDONLY );
	if( 0 > fd )
		return mild_false;

	/// find module if exist in "/proc/modules" file
	res = fread_find_string( fd, target_str__, ' ', mild_null );

	close( fd );

	return res;
}

mild_bool checkKernelModuleExist(
	mild_cstr					target__
	)
{
	return check_kernel_module_exist( target__ );
}


mild_bool check_kernel_symbol_exist(
	mild_cstr					symbol__,
	mild_u64					*addr__
	)
{
	mild_i32 fd = 0;
	mild_bool res = mild_false;
	mild_i8 symbol[ 64 ] = { 0, };

	if( mild_null == symbol__ )
		return mild_false;

	/// 전달된 문자열 앞에 공백을 추가
	/// "sys_open"이 전달되면 " sys_open"으로 변경
	/// 커널 심볼은 모두 공백으로 시작되므로 정확한 문자열 비교를 위해 문자열 생성
	symbol[ 0 ] = ' ';
	memcpy( symbol + 1, symbol__, strlen( symbol__ ) );

	/// 대상 파일의 존재 여부와 일반 파일인지 여부 확인
	if( mild_false == check_regular_filetype( PROC_SYSCALL_FILE ) )
		return mild_false;

	/// "/proc/kallsyms" 파일을 읽기 전용으로 개방
	fd = open( PROC_SYSCALL_FILE, O_RDONLY );
	if( 0 > fd )
		return mild_false;

	/// 커널 심볼에서 요청한 커널 심볼이 존재하는지 확인
	/// 3번째 인수인 구분자로 줄 바꿈을 이용하면 커널 심볼에서
	/// " sys_open\n" 형태인 이름을 정확하게 검색할 수 있음
	/// 따라서 동일한 이름이 포함된 다른 심볼을 검색하는 오류를 방지할 수 있음
	res = fread_find_string( fd, symbol, '\n', addr__ );

	close( fd );

	return res;
}

mild_bool checkKernelSymbolExist(
	mild_cstr					symbol__,
	mild_u64					*addr__
	)
{
	return check_kernel_symbol_exist( symbol__, addr__ );
}
