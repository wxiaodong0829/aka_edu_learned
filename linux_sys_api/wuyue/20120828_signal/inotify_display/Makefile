
all: inotify_display.o err.o mem_pool.o
	gcc -g -Wall $^ 
inotify_display.o: inotify_display.c err.c err.h
	gcc -g -c -Wall $^
err.o: err.c err.h
	gcc -g -c -Wall $<
mem_poo.o: mem_pool.c mem_pool.h
	gcc -g -c -Wall $<

clean:
	rm *.o
	rm a.out

.PHONY: clean
