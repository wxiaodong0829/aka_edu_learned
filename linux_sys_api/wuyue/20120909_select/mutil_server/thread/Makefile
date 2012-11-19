all: server client

server: server.c err.c err.h
	gcc server.c  err.c -Wall -o server -lpthread

client: client.c err.c err.h
	gcc client.c  err.c -g -Wall -o client
	
clean: 
	rm client server
.PHONY: clean
