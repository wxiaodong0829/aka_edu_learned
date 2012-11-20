CC=arm-linux-gcc
AS=arm-linux-as
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
OBJDUMP=arm-linux-objdump
OBJCFLAGS=--gap-fill=0xff
CFLAGS=-nostdlib
src_c = $(wildcard *.c)
src_s = $(wildcard *.s)
obj_c = $(patsubst %.c, %.o, $(src_c))
obj_s = $(patsubst %.s, %.o, $(src_s))
target = app
sd = sd

# 生成16字节的校验
$(sd).bin:$(target).bin
	./mktiny210spl.exe $< $(target)-sd.bin
$(target).bin:$(target)
	$(OBJCOPY) $(OBJCFLAGS) -O binary  $< $@

$(target):$(obj_s) $(obj_c) mem_setup.o
	$(LD)  -Tlink.lds  $^ -o $@
	$(OBJDUMP) -dxSs $@ > $(target).lst
%.o:%.c
	$(CC) -o $@ $(CFLAGS) -c $<
%.o:%.s
	$(AS) -o $@ $<

burn:
	sudo dd iflag=dsync oflag=dsync if=$(target)-sd.bin of=/dev/sdb seek=1

clean:
	-rm -f $(target)
	-rm -f *.bin
	-rm -f $(target).bin
	-rm -f $(obj_s)
	-rm -f $(obj_c)
	-rm -f *~
	-rm -f *.lst

.PHONY: clean

