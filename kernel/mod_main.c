#include <linux/kernel.h>
#include <linux/module.h>


static int __init hello_markany_openCode( void )
{
    printk( "%s: Hello Kernel!\n", __FUNCTION__ );
    return 0;
}


static void __exit bye_markany_openCode( void )
{
    printk( "%s: Bye Kernel\n", __FUNCTION__ );
}


module_init( hello_markany_openCode );
module_exit( bye_markany_openCode );

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "MarkAny Inc." );
MODULE_DESCRIPTION( "MarkAny openCode Module" );
