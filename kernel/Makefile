obj-m		:=	maOpen.o
maOpen-objs	:=	mod_main.o						\
				netlink_handler.o				\
				netlink_init.o					\
				sysfs_handler.o					\
				sysfs_init.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
