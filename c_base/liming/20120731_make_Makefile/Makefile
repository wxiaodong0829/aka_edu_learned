CC = gcc
CFLAGS = -Wall

all		:  main

main	:	main.o add.o sub.o
	gcc  main.o add.o sub.o -o main

main.o	: main.c add_sub.h
add.o	: add.c
sub.o	: sub.c

clean	:
	rm *.o 
	rm main

.PHONY	: clean
