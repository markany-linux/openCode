#include "crc.h"

/// 참조: https://www.w3.org/TR/PNG/#D-CRCAppendix


/// * CRC 초기화 값
#define CRC_INIT_VALUE      0xffffffffL


/**
 * @brief   CRC 동작을 위한 정보체
 */
typedef struct crc_setting_info
{
    /// CRC 초기화 여부
    mild_bool                   setup;

    /// CRC 테이블
    mild_u32                    table[ STRLEN_256 ];

} CRC_INFO, *PCRC_INFO;


/// * CRC 정보 관리를 위한 전역 구조체 변수 선언
CRC_INFO g_crc;


/**
 * @brief   CRC 사용을 위해 테이블을 초기화
 *          * 전역 구조체의 CRC 테이블에 값을 할당하는 초기화 작업
 *          * 한번만 수행하면 지속적으로 사용이 가능
 */
static void make_crc_table( void )
{
    mild_u32 crc = 0;
    mild_i32 i = 0;
    mild_i32 j = 0;

    /// * CRC 테이블 길이만큼 반복
    for( i = 0; i < STRLEN_256; i++ )
    {
        /// * 반복문 이터레이터를 이용
        crc = ( mild_u32 )i;

        /// * CRC 테이블 값 설정을 위한 반복
        for( j = 0; j < STRLEN_8; j++ )
        {
            /// * 테이블 값 획득을 위한 연산
            if( crc & 1 )
            {
                crc = 0xedb88320L ^ ( crc >> 1 );
            }
            else
            {
                crc = crc >> 1;
            }
            /// * 획득된 값을 테이블에 등록
            g_crc.table[ i ] = crc;
        }
    }

    /// * CRC 테이블이 생성되었음을 설정
    g_crc.setup = mild_true;
}


/**
 * @brief   버퍼에 대한 CRC 값을 실제로 획득하여 반환
 * 
 * @param   crc__       CRC 초기화 값
 * @param   buffer__    CRC를 획득하려는 버퍼
 * @param   len__       버퍼 길이
 * 
 * @return  획득된 CRC 값
 */
static mild_u32 update_crc(
    mild_u32                    crc__,
    mild_custr                  buffer__,
    mild_i32                    len__
    )
{
    mild_i32 i = 0;
    mild_u32 crc = crc__;

    if( mild_false == g_crc.setup )
        make_crc_table( );

    for( i = 0; i < len__; i++ )
    {
        crc = g_crc.table[ ( crc ^ buffer__[ i ] ) & 0xff ] ^ ( crc >> 8 );
    }

    return crc;
}


mild_u32 get_crc_value(
    mild_custr                  buffer__,
    mild_i32                    len__
    )
{
    return update_crc( CRC_INIT_VALUE, buffer__, len__ ) ^ CRC_INIT_VALUE;
}

mild_u32 getCRCValue(
    mild_custr                  buffer__,
    mild_i32                    len__
    )
{
    return get_crc_value( buffer__, len__ );
}
