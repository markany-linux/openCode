#include "sysfs_init.h"

#include "sysfs_handler.h"


/// sysfs 커널 객체
static struct kobject *openCode_kobj;


/**
 * @brief   info 파일에서 반환할 정보 설정
 * 
 * @param   netlink_load__  netlink 적재 상태
 */
static void setSysfsInfo(
    mild_bool                   netlink_load__
    )
{
    /// sysfs 버전
    info.sysfs_version = SYSFS_VERSION;

    /// netlink 정보
    info.netlink_load = netlink_load__;
    info.netlink_port = NETLINK_PORT_NUMBER;
    info.netlink_version = NETLINK_VERSION;
}


mild_bool initSysfsKernelObject(
    mild_bool                   netlink_load__
    )
{
    mild_i32 ret = 0;

    /// 커널 객체 생성, 추가 및 확인
    openCode_kobj = kobject_create_and_add( SYSFS_EXPORT_DIR, kernel_kobj );
    if( mild_null == openCode_kobj )
    {
        printk( "Fail to create sysfs/ kernel object\n" );
        return mild_false;
    }

    /// sysfs 그룹 생성
    ret = sysfs_create_group( openCode_kobj, &openCode_attr_group );

    /// 그룹 생성 확인
    if( ret )
    {
        /// 추가된 커널 객체 제거 및 실패 반환
        kobject_put( openCode_kobj );
        return mild_false;
    }

    /// info 파일 정보 설정
    setSysfsInfo( netlink_load__ );

    return mild_true;
}


void updateNetlinkLoadState(
    mild_bool                   netlink_load__
    )
{
    info.netlink_load = netlink_load__;
}


void exitSysfsKernelObject( void )
{
    kobject_put( openCode_kobj );
    printk( "openCode sysfs kernel object cleanup\n" );
}
