#include "sysfs_handler.h"

#include "lkm_version.h"
#include "access_list.h"


SYSFS_INFO info;


static ssize_t version_get(
    struct kobject              *kobj__,
    struct kobj_attribute       *attr__,
    mild_str                    buf__
    )
{
    if( mild_null == buf__ )
    {
        printk( "Invalid buffer(NULL) received\n" );
        return -EINVAL;
    }

    if( mild_false == addNewAccessList( SYSFS_INFO_FILE ) )
    {
        printk( "Fail to add netlink node list for %s\n", SYSFS_INFO_FILE );
    }

    return sprintf( buf__, "%d", LKM_VERSION );
}

static struct kobj_attribute version_attribute = __ATTR( version, 0644, version_get, NULL );


static ssize_t info_get(
    struct kobject              *kobj__,
    struct kobj_attribute       *attr__,
    mild_str                    buf__
    )
{
    if( mild_null == buf__ )
    {
        printk( "Invalid buffer(NULL) received\n" );
        return -EINVAL;
    }

    memcpy( buf__, &info, sizeof( SYSFS_INFO ) );

    if( mild_false == addNewAccessList( SYSFS_VERSION_FILE ) )
    {
        printk( "Fail to add netlink node list for %s\n", SYSFS_VERSION_FILE );
    }

    return sizeof( SYSFS_INFO );
}

static struct kobj_attribute info_attribute = __ATTR( info, 0644, info_get, NULL );


static struct attribute *openCode_attrs[ ] =
{
    &version_attribute.attr,
    &info_attribute.attr,
    NULL,
};


struct attribute_group openCode_attr_group =
{
    .attrs = openCode_attrs,
};
