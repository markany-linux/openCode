obj-m		:=	maOpen.o
maOpen-objs	:=	mod_main.o						\
				access_list.o					\
				netlink_handler.o				\
				netlink_init.o					\
				sysfs_handler.o					\
				sysfs_init.o

PWD 		:=	$(shell pwd)
INSTALL_DIR	:=	../bin

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	mv maOpen.ko $(INSTALL_DIR)/
	@printf "\nBuild Success : \e[32m%s\e[0m\n\n" "maOpen.ko"

clean:
	rm -rf $(INSTALL_DIR)/maOpen.ko
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	@printf "\nClean Success : \e[32m%s\e[0m\n\n" "$(maOpen-objs) maOpen.ko"
