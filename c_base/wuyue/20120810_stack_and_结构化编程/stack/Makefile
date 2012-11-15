
CFLAGS= -I./include -c

all:	main.o stack.so
	gcc -o all  main.o ./stack.so 

main.o: main.c
	gcc -o $@ $^ $(CFLAGS)

stack.so: stack.c
	gcc -o $@ $< -I./include -shared -fPIC

clean:
	rm *.o
	rm *.so
	rm all

.PHONY: clean
