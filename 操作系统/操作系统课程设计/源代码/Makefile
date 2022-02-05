ifneq ($(KERNELRELEASE),)
	obj-m:=pf.o
else
    KDIR:= /modules/$(shell uname -r)/build
	PWD:= $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif
