KERNEL_DIR =	./kernel
USER_DIR =	./user

all:
	$(MAKE) -C $(KERNEL_DIR)
	$(MAKE) -C $(USER_DIR)

clean:
	$(MAKE) -C $(KERNEL_DIR) clean
	$(MAKE) -C $(USER_DIR) clean
