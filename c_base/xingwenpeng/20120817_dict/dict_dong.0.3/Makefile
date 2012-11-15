CC = gcc
CFLAGS = -Wall -g -Iinclude -DDEBUG

PWD = $(shell pwd)
DIRNAME = $(notdir $(PWD))
PRJ = $(DIRNAME)

TARGET = $(PRJ)

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

all: dep $(TARGET)

dep: # generate a .depend file
	@echo "generate .depend file ok"
	@echo "# auto generated file, don't edit" > .depend
	@for i in $(SRC); do gcc -MM -Iinclude $$i >> .depend; done

ifeq (.depend, $(wildcard .depend))
include .depend
endif

$(TARGET): $(OBJ)
	gcc $^ -o $@ $(CFLAGS)

clean:
	rm $(OBJ)
	rm $(TARGET)

.PHONY: clean dep all 
