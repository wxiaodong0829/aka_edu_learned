CC = gcc
CFLAGS = -Wall -g

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
	@echo "generate .depend file ok"
	@echo "# auto generated file, don't edit" > .depend
	#@for i in $(SRC); do gcc -MM $$i >> .depend; done
	gcc -MM $(SRC) > .depend

ifeq (.depend, $(wildcard .depend))
include .depend
endif

clean:
	rm $(OBJ)
	rm $(TARGET)




