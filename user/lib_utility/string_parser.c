#include "string_parser.h"

#include <string.h>
#include <stdio.h>


void print_current_line(
    mild_str                    buf__
    )
{
    while( '\n' != *buf__ )
    {
        printf( "%c", *buf__ );
        buf__++;
    }
}


mild_i32 get_target_string_offset(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 i = 0;
    mild_i32 j = 0;
    mild_i32 length = strlen( target__ );

    if( ( mild_null == target__ ) || ( mild_null == buf__ ) )
        return -1;

    if( 0 > len__ )
        return -1;

    /// 버퍼 길이만큼 반복 
    for( ; i < len__; i++ )
    {
        /// 현재 위치에서 대상 문자열 길이 만큼 반복
        for( j = 0; j < length; j++ )
        {
            /// 대상 문자열과 동일한 문자가 아니면 반복을 빠져나감
            if( *( buf__ + i + j ) != *( target__ + j ) )
                break;
        }

        /// 문자열 길이와 반복 길이가 동일한지 여부 확인
        if( length == j )
            return i;
    }

    /// 문자열 찾기 실패
    return -1;
}

mild_i32 getTargetStringOffset(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_target_string_offset( target__, buf__, len__ );
}


/**
 * @brief   문자열 위치와 존재 여부 확인 처리 공용 핸들러
 * 
 * @param   target__    찾을 문자열
 * @param   buf__       검색 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  찾을 문자열이 존재하면 변위 값, 없으면 -1
 */
static mild_i32 common_string_checker(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{

    if( ( mild_null == target__ ) || ( mild_null == buf__ ) )
        return -1;
        
    if( 0 > len__ )
        return -1;

    /// 확인 결과를 반환
    return get_target_string_offset( target__, buf__, len__ );
}


mild_str get_target_string_ptr(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 cnt = 0;

    /// 대상 문자열 존재 여부 확인
    /// ! 포인터 위치 반환을 위해 변위 값이 필요하여 변수를 사용
    /// ! -1 이 반환되면, 존재하지 않음에도 포인터 위치가 반환되므로 반드시 필요
    cnt = common_string_checker( target__, buf__, len__ );

    /// 존재하지 않으면 NULL 반환
    if( -1 == cnt )
        return mild_null;

    /// 존재 시, 포인터에 변위를 더해 위치를 반환
    return ( mild_str )( buf__ + cnt );
}

mild_str getTargetStringPtr(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_target_string_ptr( target__, buf__, len__ );
}


mild_bool check_target_string_exist(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    /// 대상 문자열이 존재하지 않으면 false 반환
    if( -1 == common_string_checker( target__, buf__, len__ ) )
        return mild_false;

    /// 존재 시, true 반환
    return mild_true;
}

mild_bool checkTargetStringExist(
    mild_cstr                   target__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return check_target_string_exist( target__, buf__, len__ );
}


mild_i32 get_target_char_offset(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 i = 0;

    if( ( mild_null == buf__ ) || ( 0 > len__ ) )
        return -1;

    /// 버퍼 길이만큼 반복
    for( ; i < len__; i++ )
    {
        /// 문자가 확인할 문자인지 여부 확인
        /// 요청 문자라면 문자까지의 변위 값을 그대로 반환
        if( char__ == *( buf__ + i ) )
            return i;
    }

    /// 반환 없이 도착하면 해당 문자가 없음을 반환
    return -1;
}

mild_i32 getTargetCharOffset(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_target_char_offset( char__, buf__, len__ );
}


/**
 * @brief   문자 위치와 존재 여부 확인 처리 공용 핸들러
 * 
 * @param   char__  찾을 문자
 * @param   buf__   검색 버퍼
 * @param   len__   버퍼 길이
 * 
 * @return  찾을 문자가 존재하면 변위 값, 없으면 -1
 */
static mild_i32 common_char_checker(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    /// 전달 버퍼와 길이 확인
    if( ( mild_null == buf__ ) || ( 0 > len__ ) )
        return -1;

    /// 확인 결과를 반환
    return get_target_char_offset( char__, buf__, len__ );
}


mild_str get_target_char_ptr(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 cnt = 0;

    /// 문자 존재 여부 확인 및 변위 획득
    cnt = common_char_checker( char__, buf__, len__ );

    /// 존재하지 않으면 NULL 반환
    if( -1 == cnt )
        return mild_null;

    /// 존재 시, 존재 포인터 계산하여 반환
    return ( mild_str )( buf__ + cnt );
}

mild_str getTargetCharPtr(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_target_char_ptr( char__, buf__, len__ );
}


mild_bool check_target_char_exist(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    /// 대상 문자열 존재 여부 확인
    if( -1 == common_char_checker( char__, buf__, len__ ) )
        return mild_false;

    /// 존재 시, true 반환
    return mild_true;
}

mild_bool checkTargetCharExist(
    mild_i8                     char__,
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return check_target_char_exist( char__, buf__, len__ );
}


mild_i32 get_next_line_offset(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 i = 0;

    if( ( mild_null == buf__ ) || ( 0 > len__ ) )
        return -1;

    /// 버퍼 길이만큼 반복
    for( ; i < len__; i++ )
    {
        /// 현재 문자가 '\n'인지 확인하고, 변위 값을 반환
        if( '\n' == *( buf__ + i ) )
            return i;
    }

    /// 반환되지 않았다면, 존재하지 않음을 반환
    return -1;
}

mild_i32 getNextLineOffset(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_next_line_offset( buf__, len__ );
}


mild_str get_next_line_ptr(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 offset = 0;

    if( ( mild_null == buf__ ) || ( 0 > len__ ) )
        return mild_null;

    /// '\n'까지의 길이를 획득
    offset = get_next_line_offset( buf__, len__ );

    /// 존재하지 않으면 NULL 포인터를 반환
    if( -1 == offset )
        return mild_null;

    /// 전달 포인터에 변위를 더해 반환
    return ( mild_str )( buf__ + offset );
}

mild_str getNextLinePtr(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_next_line_ptr( buf__, len__ );
}


mild_i32 get_current_line_start_offset(
    mild_cstr                   buf__
    )
{
    mild_i32 cnt = 0;

    if( mild_null == buf__ )
        return -1;

    /// 현재 위치가 '\n'일 때까지 반복
    while( '\n' != *buf__ )
    {
        /// 한 문자 전으로 이동
        buf__--;
        /// 변위 증가
        cnt++;
    }

    /// 변위 값을 반환
    return cnt;
}

mild_i32 getCurrentLineStartOffset(
    mild_cstr                   buf__
    )
{
    return get_current_line_start_offset( buf__ );
}


mild_str get_current_line_start_ptr(
    mild_cstr                   buf__
    )
{
    mild_i32 cnt = 0;

    if( mild_null == buf__ )
        return mild_null;

    /// 이전 라인의 '\n' 까지 변위 획득
    cnt = get_current_line_start_offset( buf__ );
    
    /// 현재 위치에 변위를 빼서 반환
    return ( mild_str )( buf__ - cnt );
}

mild_str getCurrentLineStartPtr(
    mild_cstr                   buf__
    )
{
    return get_current_line_start_ptr( buf__ );
}


mild_i32 get_next_space_offset(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 cnt = 0;

    if( ( mild_null == buf__ ) || ( 0 > len__ ) )
        return -1;

    /// 바로 다음 위치가 ' '(공백)일 때까지 반복
    while( ' ' != *buf__ )
    {
        /// 다음 위치로 포인터 이동
        buf__++;
        /// 변위 값 증가
        cnt++;

        /// 다음 위치가 길이를 벗어 났는지 확인
        if( len__ <= cnt )
        {
            /// 오류 값 설정 후, 반복문을 빠져나감
            cnt = -1;
            break;
        }
    }

    /// 변위값 반환
    return cnt;
}

mild_i32 getNextSpaceOffset(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_next_space_offset( buf__, len__ );
}


mild_str get_next_space_ptr(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    mild_i32 cnt = 0;

    if( ( mild_null == buf__ ) || ( 0 > len__ ) )
        return mild_null;

    /// 다음 공백까지의 변위를 획득
    cnt = get_next_space_offset( buf__, len__ );
    /// 존재하지 않으면 NULL 반환
    if( -1 == cnt )
        return mild_null;

    /// 존재하면, 전달 위치에 변위 값을 더해 반환
    return ( mild_str )( buf__ + cnt );
}

mild_str getNextSpacePtr(
    mild_cstr                   buf__,
    mild_i32                    len__
    )
{
    return get_next_space_ptr( buf__, len__ );
}


mild_i32 get_previous_space_offset(
    mild_cstr                   buf__
    )
{
    mild_i32 cnt = 0;

    if( mild_null == buf__ )
        return -1;

    /// 현재 위치가 공백일 때까지 반복
    while( ' ' != *buf__ )
    {
        /// 이전 위치로 포인터 이동
        buf__--;
        /// 변위 값 증가
        cnt++;
    }

    /// 변위 값 반환
    return cnt;
}

mild_i32 getPreviousSpaceOffset(
    mild_cstr                   buf__
    )
{
    return get_previous_space_offset( buf__ );
}


mild_str get_previous_space_ptr(
    mild_cstr                   buf__
    )
{
    mild_i32 cnt = 0;

    if( mild_null == buf__ )
        return mild_null;

    /// 바로 이전 공백의 변위 값을 획득
    cnt = get_previous_space_offset( buf__ );
    /// 존재하지 않으면 NULL을 반환
    if( -1 == cnt )
        return mild_null;

    /// 전달 위치에 변위 값을 빼서 반환
    return ( mild_str )( buf__ - cnt );
}

mild_str getPreviousSpacePtr(
    mild_cstr                   buf__
    )
{
    return get_previous_space_ptr( buf__ );
}


// FIXME: getNextSpaceOffset( )으로 대체하고, 제거해야 함
mild_u32 get_space_pos(
	mild_str					str__
	)
{
	mild_u32 cnt = 0;

	while( ' ' != *str__ )
	{
		str__++;
		cnt++;
	}

	return cnt;
}

// FIXME: getNextSpaceOffset( )으로 대체하고, 제거해야 함
mild_u32 getSpacePos(
	mild_str					str__
    )
{
    return get_space_pos( str__ );
}


mild_i32 current_line_skip(
    mild_str                    *ptr__
    )
{
    mild_i32 cnt = 0;

    while( '\n' != *( *ptr__ )++ )
    {
        cnt++;
    }

    return cnt;
}

mild_i32 CurrentlineSkip(
    mild_str                    *ptr__
    )
{
    return current_line_skip( ptr__ );
}
