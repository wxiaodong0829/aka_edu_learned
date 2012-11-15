CC = gcc
CFLAGS = -Wall
TARGET = demo 
SRC2 = $(wildcard *.[ch])
OBJ = $(SRC:%.c=%.o)
TEST = $(subst c,o,$(SRC))
T2 = $(patsubst %.h, %.o, $(SRC))

STRIP = $(strip hello aka    world      )
FIND = $(findstring akae, hello aka    world      )
HEADER = $(filter-out %d.c, $(SRC))
SRC  = $(filter-out %-ok.c, $(SRC2))
SORT = $(sort $(STRIP))

PWD = $(shell pwd)
DIR = $(dir $(PWD))
NDIR = $(notdir $(PWD))
SUF = $(suffix $(SRC))
BASE = $(basename $(SRC))
ADDSUF = $(addsuffix .test, $(BASE))
ADDPRE = $(addprefix pre-, $(ADDSUF))
JOIN = $(join aaa bbb c d e, 111 222 333)

all: $(TARGET) 
	echo $(PWD)
	echo $(DIR)
	echo $(NDIR)
	echo $(SUF)
	echo $(BASE)
	echo $(ADDSUF)
	echo $(ADDPRE)
	echo $(JOIN)
#	cd var; make
#	make -C var
	echo hello

string:
	@echo SRC $(SRC)
	@echo SRC2 $(SRC2)
	@echo H $(HEADER)
	@echo OBJ $(OBJ)
	@echo TEST $(TEST)
	@echo T2 $(T2)
	@echo .$(STRIP).
	@echo .$(FIND).
	@echo .$(SORT).
	
$(TARGET): $(OBJ)
	gcc $^ -o $@

main.o: main.c head.h
add.o: add.c
sub.o: sub.c head.h

clean:
	rm *.o
	rm main

.PHONY: clean

