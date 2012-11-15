src = $(wildcard *.c)
obj = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall -g -DDEBUG -L~/wd_文档/lib_dong 

all:$(obj)
$(obj): %:%.c
			$(CC) $(CFLAGS) $< -o $@

.PHONY:clean

clean:
	@rm $(obj) 
