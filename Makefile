KERNEL_DIR =	./kernel
USER_DIR =	./user

ifndef MODE
	MODE =	C
endif

ifeq ($(MODE), C)
	SOURCE_DIR = c_src
else
	SOURCE_DIR = src
endif

all:
	$(MAKE) -C $(KERNEL_DIR)
	$(MAKE) -C $(USER_DIR)/$(SOURCE_DIR)

clean:
	$(MAKE) -C $(KERNEL_DIR) clean
	$(MAKE) -C $(USER_DIR)/$(SOURCE_DIR) clean
