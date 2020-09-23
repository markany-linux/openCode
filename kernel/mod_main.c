#include "kcommon.h"

#include <linux/init.h>

#include "sysfs_init.h"
#include "netlink_init.h"
#include "access_list.h"


/**
 * @brief   커널 모듈 초기화 함수
 *          insmod 명령으로 커널 영역에 적재될 때 호출
 * 
 * @return  초기화 성공 시 0, 실패 시 -1
 */
static int __init hello_markany_openCode( void )
{
    mild_bool netlink_load = mild_false;

    printk( "%s: Hello Kernel! This is openCode Kernel Module\n", __FUNCTION__ );

    /// netlink 커널 객체 생성 및 결과 획득
    netlink_laod = initNetLinkSocket( );
    /// netlink 생성 실패 확인
    if( mild_false == netlink_load )
    {
        printk( "Fail to initialize netlink\n" );
    }

    /// sysfs 객체 초기화 및 netlink 결과 전달
    if( mild_false == initSysfsKernelObject( netlink_load ) )
    {
        /// sysfs 객체 생성 실패 시, 커널 모듈을 적재하지 않도록 구성
        printk( "Fail to initialize sysfs kernel object\nFail to load openCode Kernel Module\n\n" );
        return -1;
    }

    return 0;
}


/**
 * @brief   커널 모듈 정리 함수
 *          rmmod 명령으로 제거될 때 호출
 */
static void __exit bye_markany_openCode( void )
{
    /// netlink 해제
    exitNetLinkSocket( );

    /// sysfs 객체 해제
    exitSysfsKernelObject( );

    /// 존재할 지 모르는 접근 리스트를 모두 해제
    cleanupAccessList( );

    printk( "%s: Bye Kernel...\n", __FUNCTION__ );
}


/// 커널 모듈 init 함수 설정
module_init( hello_markany_openCode );
/// 커널 모듈 exit 함수 설정
module_exit( bye_markany_openCode );

/// 라이선스 등의 정보 설정
MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "MarkAny Inc." );
MODULE_DESCRIPTION( "MarkAny openCode Module" );
