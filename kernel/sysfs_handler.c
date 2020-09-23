#include "sysfs_handler.h"

#include "lkm_version.h"
#include "access_list.h"


SYSFS_INFO info;


/**
 * @brief   version 파일에 대한 읽기 처리기
 *          * 내부적으로 접근 정보를 추가
 * 
 * @param   kobj__  커널 객체
 * @param   attr__  속성
 * @param   buf__   반환 버퍼
 * 
 * @return  반환 길이
 */
static ssize_t version_get(
    struct kobject              *kobj__,
    struct kobj_attribute       *attr__,
    mild_str                    buf__
    )
{
    /// 버퍼 확인
    if( mild_null == buf__ )
    {
        printk( "Invalid buffer(NULL) received\n" );
        return -EINVAL;
    }

    /// version 파일 접근 정보를 리스트에 추가
    if( mild_false == addNewAccessList( SYSFS_INFO_FILE ) )
    {
        /// 리스트 추가 실패가 읽기 실패는 아니므로 정보만 출력
        printk( "Fail to add netlink node list for %s\n", SYSFS_INFO_FILE );
    }

    /// openCode 커널 모듈 버전 반환
    return sprintf( buf__, "%d", LKM_VERSION );
}

/// version 가상 파일 속성 값 설정
/// * 노출 파일명, 권한, 처리기 순으로 등록
static struct kobj_attribute version_attribute = __ATTR( version, 0644, version_get, NULL );


/**
 * @brief   info 파일에 대한 읽기 처리기
 * 
 * @param   kobj__  커널 객체
 * @param   attr__  속성
 * @param   buf__   반환 버퍼
 * 
 * @return  반환 길이
 */
static ssize_t info_get(
    struct kobject              *kobj__,
    struct kobj_attribute       *attr__,
    mild_str                    buf__
    )
{
    /// 버퍼 확인
    if( mild_null == buf__ )
    {
        printk( "Invalid buffer(NULL) received\n" );
        return -EINVAL;
    }

    /// 현재 설정된 정보를 반환 버퍼로 복사
    memcpy( buf__, &info, sizeof( SYSFS_INFO ) );

    /// info 파일 접근 정보를 리스트에 추가
    if( mild_false == addNewAccessList( SYSFS_VERSION_FILE ) )
    {
        /// 리스트 추가 실패가 읽기 실패는 아니므로 정보만 출력
        printk( "Fail to add netlink node list for %s\n", SYSFS_VERSION_FILE );
    }

    /// 구조체 길이 반환
    return sizeof( SYSFS_INFO );
}

/// info 가상 파일 속성 값 설정
static struct kobj_attribute info_attribute = __ATTR( info, 0644, info_get, NULL );


/// 생성된 version, info 속성을 하나로 설정
static struct attribute *openCode_attrs[ ] =
{
    &version_attribute.attr,
    &info_attribute.attr,
    NULL,
};


/// 속성 그룹 설정
struct attribute_group openCode_attr_group =
{
    .attrs = openCode_attrs,
};
