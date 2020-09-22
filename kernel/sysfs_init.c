#include "sysfs_init.h"

#include "sysfs_handler.h"


static struct kobject *openCode_kobj;


static void setSysfsInfo(
    mild_bool                   netlink_load__
    )
{
    info.sysfs_version = MA_VERSION_MAKER( SYSFS_MAJOR_VERSION, SYSFS_MINOR_VERSION, SYSFS_PATCH_VERSION, SYSFS_CUSTOM_VERSION );

    info.netlink_load = netlink_load__;
    info.netlink_port = NETLINK_PORT_NUMBER;
    info.netlink_version = MA_VERSION_MAKER( SYSFS_MAJOR_VERSION, SYSFS_MINOR_VERSION, SYSFS_PATCH_VERSION, SYSFS_CUSTOM_VERSION );
}


mild_bool initSysfsKernelObject(
    mild_bool                   netlink_load__
    )
{
    mild_i32 ret = 0;

    openCode_kobj = kobject_create_and_add( SYSFS_EXPORT_DIR, kernel_kobj );
    if( mild_null == openCode_kobj )
    {
        printk( "Fail to create sysfs/ kernel object\n" );
        return mild_false;
    }

    ret = sysfs_create_group( openCode_kobj, &openCode_attr_group );

    if( ret )
    {
        kobject_put( openCode_kobj );
        return mild_false;
    }

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
