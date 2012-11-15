mysort	:	main.o other.o
	gcc -o mysort main.o other.o
main.o	:	main.c
	gcc -c main.c
other.o	:	other.c
	gcc -c other.c

clean	:
	rm -f *.o mysort
