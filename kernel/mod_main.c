#include "kcommon.h"

#include <linux/init.h>

#include "sysfs_init.h"
#include "netlink_init.h"


/**
 * @brief   커널 모듈 초기화 함수
 *          insmod 명령으로 커널 영역에 적재될 때 호출
 * 
 * @return  초기화 성공 시 0, 실패 시 -1
 */
static int __init hello_markany_openCode( void )
{
    printk( "%s: Hello Kernel!\n", __FUNCTION__ );

    if( mild_false == initNetLinkSocket( ) )
    {
        printk( "Fail to initialize netlink\n" );
        return -1;
    }

    /// sysfs 객체 초기화
    if( mild_false == initSysfsKernelObject( mild_true ) )
    {
        printk( "Fail to initialize sysfs kernel object\n" );
        return -1;
    }

    return 0;
}


/**
 * @brief   커널 모듈 정리 함수
 *          rmmod 명령으로 제거될 때 호출
 * 
 */
static void __exit bye_markany_openCode( void )
{
    exitNetLinkSocket( );

    /// sysfs 객체 해제
    exitSysfsKernelObject( );

    printk( "%s: Bye Kernel\n", __FUNCTION__ );
}


/// 커널 모듈 init 함수 설정
module_init( hello_markany_openCode );
/// 커널 모듈 exit 함수 설정
module_exit( bye_markany_openCode );

/// 라이선스 등의 정보 설정
MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "MarkAny Inc." );
MODULE_DESCRIPTION( "MarkAny openCode Module" );
