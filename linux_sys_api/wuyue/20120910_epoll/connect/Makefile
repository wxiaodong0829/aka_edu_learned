all: server client client_epoll

server: server.c err.c err.h
	gcc server.c  err.c -Wall -o server -g

client_epoll: client_epoll.c err.c err.h
	gcc client_epoll.c  err.c -g -Wall -o client_epoll

client: client.c err.c err.h
	gcc client.c  err.c -g -Wall -o client
	
clean: 
	rm client server
.PHONY: clean
