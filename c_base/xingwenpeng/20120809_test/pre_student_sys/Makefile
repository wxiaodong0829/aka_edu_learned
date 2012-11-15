CC = gcc
CFLAGS = -Wall -g #-DDEBUG

PWD = $(shell pwd)
DIRNAME = $(notdir $(PWD))
PRJ = $(DIRNAME)

TARGET = $(PRJ)

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

all: dep $(TARGET)

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

$(TARGET): $(OBJ)
	gcc $^ -o $@

clean:
	rm $(OBJ)

distclean:
	rm $(OBJ)
	rm $(TARGET)
	
