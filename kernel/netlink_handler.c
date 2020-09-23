#include "netlink_handler.h"

#include <linux/cred.h>

#include "access_list.h"


struct sock *g_netlink_socket;


/**
 * @brief   로그가 존재하지 않을 경우의 반환 데이터 생성 및 반환
 * 
 * @param   log__   정보 설정 구조체
 */
static void set_no_log_info(
    PNETLINK_DATA               log__
    )
{
    const struct cred *cr = get_current_cred( );

    log__->uid = ( mild_i32 )cr->uid.val;
    log__->pid = current->pid;
    memcpy( log__->fname, NETLINK_NO_LOG_MESSAGE, strlen( NETLINK_NO_LOG_MESSAGE ) );
    memcpy( log__->task, current->comm, strlen( current->comm ) );
    log__->remain = mild_false;
}


void netlink_log_handler(
    struct sk_buff              *skb__
    )
{
    mild_i32 pid = 0;
    NETLINK_DATA node = { 0, };
    PNETLINK_DATA ptr = mild_null;
    struct nlmsghdr *msg_hdr = mild_null;
    struct sk_buff *skb_out = mild_null;
    

    /// 전달 받은 netlink 헤더 획득
    msg_hdr = ( struct nlmsghdr* )skb__->data;

    /// 헤더에 전달된 실 데이터 포인터 획득
    ptr = nlmsg_data( msg_hdr );

    /// INFO: 프로그램이 전달한 값으로 각종 처리 가능한 위치
    /// 응답 반환을 위해 전달 PID 값 획득
    pid = msg_hdr->nlmsg_pid;

    /// 반환할 sk_buff 생성 및 확인
    skb_out = nlmsg_new( sizeof( NETLINK_DATA ), 0 );
    if( !skb_out )
    {
        printk( "Fail to new sk_buff\n" );
        return;
    }

    /// 생성한 sk_buff에서 netlink 헤더 획득
    msg_hdr = nlmsg_put( skb_out, 0, 0, NLMSG_DONE, sizeof( NETLINK_DATA ), 0 );
    /// 그룹 ID 설정
    NETLINK_CB( skb_out ).dst_group = 0;

    /// 리스트에 노드가 존재하는지 여부 확인
    if( mild_false == checkAccessListRemain( ) )
    {
        /// 노드가 없음을 반환 버퍼에 기록
        set_no_log_info( &node );
    }
    else
    {
        /// 반환 노드 획득
        if( mild_false == getAccessList( &ptr ) )
        {
            /// 획득 실패 시, 노드 없음을 반환 버퍼에 기록
            /// INFO: 내부 오류로 정보를 반환도 고려
            set_no_log_info( &node );
        }
        else
        {
            /// 획득 노드 값을 반환 버퍼로 복사
            /// 복사하지 않는 경우, 노드 메모리 해제 불가 문제 발생
            memcpy( &node, ptr, sizeof( NETLINK_DATA ) );
            /// 획득된 노드를 해제
            kfree( ptr );
        }
    }

    /// 반환 메시지 데이터 영역에 반환 정보를 복사
    memcpy( nlmsg_data( msg_hdr ), &node, sizeof( NETLINK_DATA ) );

    /// 호출자에게 반환 정보를 반환
    if( 0 > nlmsg_unicast( g_netlink_socket, skb_out, pid ) )
    {
        printk( "Fail to sending back user\n" );
    }

    /// INFO: 반환을 위해 생성한 skb_out를 해제하면 정상적으로 반환되지 않음으로 주의
    ///       반환 sbk_out은 정상적으로 반환되면 커널에서 해제하므로 처리 불필요
}
