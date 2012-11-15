tail	: mem.o main.o
	cc -o tail mem.o main.o

mem.o	: mem.c mem.h
	cc -c mem.c

main.o	: main.c mem.h
	cc -c main.c
