#include "access_list.h"

#include <linux/list.h>
#include <linux/slab.h>
#include <linux/cred.h>


/// 리스트 동기화 처리를 위한 spinlock 선언 및 초기화
DEFINE_SPINLOCK( access_info_lock );

/// 리스트의 헤드 선언 및 초기화
LIST_HEAD( access_info_head );


/**
 * @brief   리스트에서 관리할 정보 구조
 */
typedef struct sysfs_access_info_management_list
{
    /// 보관하고 반환할 접근 정보
    PNETLINK_DATA               data;

    /// 리스트 헤드
    struct list_head            access_list_head;

} SYS_ACCESS_LIST, *PSYS_ACCESS_LIST;


/**
 * @brief   리스트 관리 구조체 메모리 해제
 * 
 * @param   data__  데이터 해제 여부
 * @param   list__  해제할 관리 구조체
 */
static void free_access_list(
    mild_bool                   data__,
    PSYS_ACCESS_LIST            list__
    )
{
    /// NULL 전달 시 처리하지 않음
    if( mild_null == list__ )
        return;

    /// 데이터 해제 여부 확인
    if( mild_false != data__ )
    {
        /// 데이터 해제 요청 시, 데이터가 존재하는지 여부 확인
        if( mild_null != list__->data )
        {
            /// 데이터 정보를 초기화
            memset( list__->data, 0x00, sizeof( NETLINK_DATA ) );
            /// 데이터 구조체 메모리 해제
            kfree( list__->data );
        }
    }

    /// 관리 정보 초기화
    memset( list__, 0x00, sizeof( SYS_ACCESS_LIST ) );
    /// 관리 구조체 메모리 해제
    kfree( list__ );
}


/**
 * @brief   관리 구조체 메모리를 할당하고 반환
 * 
 * @param   list__  반환할 관리 구조체
 * 
 * @return  메모리 할당 성공 true, 실패 false
 */
static mild_bool malloc_access_list(
    PSYS_ACCESS_LIST            *list__
    )
{
    PSYS_ACCESS_LIST list = mild_null;

    /// 관리 구조체 메모리 할당 및 확인
    list = ( PSYS_ACCESS_LIST )kmalloc( sizeof( SYS_ACCESS_LIST ), GFP_KERNEL );
    if( mild_null == list )
    {
        printk( "Fail to allocate kernel memory\n" );
        return mild_false;
    }

    /// 할당된 메모리 초기화
    memset( list, 0x00, sizeof( SYS_ACCESS_LIST ) );

    /// 관리 구조체의 데이터 멤버 메모리 할당 및 확인
    list->data = ( PNETLINK_DATA )kmalloc( sizeof( NETLINK_DATA ), GFP_KERNEL );
    if( mild_null == list->data )
    {
        /// 실패 시, 관리 구조체 메모리를 해제 및 실패 반환
        free_access_list( mild_true, list );
        return mild_false;
    }

    /// 할당된 데이터 메모리 초기화
    memset( list->data, 0x00, sizeof( NETLINK_DATA ) );

    /// 관리 구조체 반환
    *list__ = list;

    return mild_true;
}


mild_bool addNewAccessList(
    mild_str                    file__
    )
{
    PSYS_ACCESS_LIST list = mild_null;
    const struct cred *cr = get_current_cred( );

    /// 새로운 관리 노드와 데이터 동적 생성
    if( mild_false == malloc_access_list( &list ) )
        return mild_false;

    /// PID, UID, 파일/프로세스 명 값 등록
    list->data->pid = current->pid;
    list->data->uid = ( mild_i32 )cr->uid.val;
    memcpy( list->data->fname, file__, strlen( file__ ) );
    memcpy( list->data->task, current->comm, strlen( current->comm ) );
    list->data->remain = mild_false;

    /// 리스트에 노드 추가
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

    /// 리스트 순환
    list_for_each_safe( pos, tmp, &access_info_head )
    {
        /// 관리 노드 획득
        list = list_entry( pos, SYS_ACCESS_LIST, access_list_head );

        /// 리스트에서 획득한 관리 노드를 제거
        list_del( pos );

        /// 남아 있는 노드 정보를 반환 전에 설정
        /// 먼저 노드를 제거하지 않으면 항상 노드가 남아 있으므로 주의
        list->data->remain = checkAccessListRemain( );

        /// 데이터 반환
        *data__ = list->data;

        /// 관리 노드만 해제하도록 해제 함수 호출
        free_access_list( mild_false, list );

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
        /// 관리 노드 획득
        list = list_entry( pos, SYS_ACCESS_LIST, access_list_head );

        /// 리스트에서 획득한 관리 노드를 제거
        list_del( pos );

        /// 관리 노드와 데이터까지 모두 해제하도록 해제 함수 호출
        free_access_list( mild_true, list );
    }

    spin_unlock( &access_info_lock );
}
