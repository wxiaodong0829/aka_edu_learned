src = $(wildcard *.c)
objs = $(patsubst %.c, %.o, $(src))

target = app
CC = gcc
CFLAGS = -Wall -g -c
LDFLAGS =

all:$(target)
$(target):$(objs)
	$(CC) $^ -o $@
$(obj):%.o:%.c
	$(CC)  $(CFLAGS) $< -o $@

clean:
	-rm -f $(target) $(objs)
	
.PHONY:clean all
