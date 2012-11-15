CFLAGS= -c -Iinclude

app: main.o stack.so
	gcc main.o ./stack.so -o app

stack.so: stack.c
	gcc stack.c -o stack.so -shared -fPIC
main.o: main.c
	gcc main.c $(CFLAGS)
clean:
	rm *.o
	rm stack.so
	rm app
.PHONY: clean
