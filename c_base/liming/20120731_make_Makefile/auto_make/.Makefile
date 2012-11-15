CC = gcc
CFLAGS = -Wall
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

all: $(TARGET)
	echo $(SRC)
	echo $(OBJ)

$(TARGET): $(OBJ)
	gcc $^ -o $@

main.o: main.c add_sub.h
add.o: add.c
sub.o: sub.c

clean:
	rm *.o
	rm main
