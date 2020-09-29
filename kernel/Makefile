obj-m		:=	maOpen.o
maOpen-objs	:=	mod_main.o						\
				access_list.o					\
				netlink_handler.o				\
				netlink_init.o					\
				sysfs_handler.o					\
				sysfs_init.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
