CC = gcc
CFLAGS = -Wall -g -I./include#-DDEBUG

PWD = $(shell pwd)
DIRNAME = $(notdir $(PWD))
PRJ = $(DIRNAME)

TARGET = $(PRJ)

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

all: dep $(TARGET)

$(TARGET): $(OBJ)
	gcc $^ -o $@

dep: # generate a .depend file
#echo "generate .depend file ok"
	@echo "# auto generated file, don't edit" > .depend
	@for i in $(SRC); do gcc -MM $$i >> .depend; done
#	gcc -MM $(SRC) >> .depend
#	@gcc -MM main.c > .depend
#	@gcc -MM add.c  > .depend
#	@gcc -MM sub.c  > .depend

ifeq (.depend, $(wildcard .depend))
include .depend
endif


clean:
	rm $(OBJ)

distclean:
	rm $(OBJ)
	rm $(TARGET)
.PHONY:	clean distclean dep
