#include "access_list.h"

#include <linux/list.h>
#include <linux/slab.h>
#include <linux/cred.h>


DEFINE_SPINLOCK( access_info_lock );

LIST_HEAD( access_info_head );


typedef struct sysfs_access_info_management_list
{
    PNETLINK_DATA               data;

    struct list_head            access_list_head;

} SYS_ACCESS_LIST, *PSYS_ACCESS_LIST;


static void free_access_list(
    PSYS_ACCESS_LIST            list__
    )
{
    if( mild_null == list__ )
        return;

    memset( list__, 0x00, sizeof( SYS_ACCESS_LIST ) );
    kfree( list__ );
}


static mild_bool malloc_access_list(
    PSYS_ACCESS_LIST            *list__
    )
{
    PSYS_ACCESS_LIST list = mild_null;

    list = ( PSYS_ACCESS_LIST )kmalloc( sizeof( SYS_ACCESS_LIST ), GFP_KERNEL );
    if( mild_null == list )
    {
        printk( "Fail to allocate kernel memory\n" );
        return mild_false;
    }
    memset( list, 0x00, sizeof( SYS_ACCESS_LIST ) );

    list->data = ( PNETLINK_DATA )kmalloc( sizeof( NETLINK_DATA ), GFP_KERNEL );
    if( mild_null == list->data )
    {
        free_access_list( list );
        return mild_false;
    }
    memset( list->data, 0x00, sizeof( NETLINK_DATA ) );

    *list__ = list;

    return mild_true;
}


mild_bool addNewAccessList(
    mild_str                    file__
    )
{
    PSYS_ACCESS_LIST list = mild_null;
    const struct cred *cr = get_current_cred( );

    if( mild_false == malloc_access_list( &list ) )
        return mild_false;

    list->data->pid = current->pid;
    list->data->uid = ( mild_i32 )cr->uid.val;
    memcpy( list->data->fname, file__, strlen( file__ ) );
    memcpy( list->data->task, current->comm, strlen( current->comm ) );
    list->data->remain = mild_false;

    spin_lock( &access_info_lock );
    list_add_tail( &list->access_list_head, &access_info_head );
    spin_unlock( &access_info_lock );

    return mild_true;
}


mild_bool checkAccessListRemain( void )
{
    if( 0 != list_empty( &access_info_head ) )
        return mild_false;

    return mild_true;
}


mild_bool getAccessList(
    PNETLINK_DATA               *data__
    )
{
    PSYS_ACCESS_LIST list = mild_null;
    struct list_head *pos = mild_null;
    struct list_head *tmp = mild_null;

    spin_lock( &access_info_lock );

    list_for_each_safe( pos, tmp, &access_info_head )
    {
        list = list_entry( pos, SYS_ACCESS_LIST, access_list_head );

        list_del( pos );

        list->data->remain = checkAccessListRemain( );

        *data__ = list->data;

        free_access_list( list );

        spin_unlock( &access_info_lock );

        return mild_true;
    }

    spin_unlock( &access_info_lock );

    return mild_false;
}


void cleanupAccessList( void )
{
    PSYS_ACCESS_LIST list = mild_null;
    struct list_head *pos = mild_null;
    struct list_head *tmp = mild_null;

    spin_lock( &access_info_lock );

    list_for_each_safe( pos, tmp, &access_info_head )
    {
        list = list_entry( pos, SYS_ACCESS_LIST, access_list_head );

        list_del( pos );

        free_access_list( list );
    }

    spin_unlock( &access_info_lock );
}
