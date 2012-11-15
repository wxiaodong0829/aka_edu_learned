CC = gcc
CFLAGS = -Wall

all:  main
	
main: main.o add.o sub.o
	@echo The most newest pre.. $?
	gcc main.o add.o sub.o -o main

main.o: main.c head.h
add.o: add.c
sub.o: sub.c head.h

clean:
	rm *.o
	rm main

.PHONY: clean

