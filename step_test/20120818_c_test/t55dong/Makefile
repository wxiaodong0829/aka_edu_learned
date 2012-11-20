src = $(wildcard *.c)
obj = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall -g

all:$(obj)
$(obj): %:%.c
			$(CC) $(CFLAGS) $< -o $@

.PHONY:clean

clean:
	@rm $(obj) 
