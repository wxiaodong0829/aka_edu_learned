ifneq ($(KERNELRELEASE),)

obj-m:=driver.o

else

KERNELSRC :=/home/bryan/work/kernel-2.6.27-android_ok


modules:
	make -C $(KERNELSRC) SUBDIRS=$(PWD) $@

clean:
	rm -f *.o *.ko *.mod.c *~

endif
