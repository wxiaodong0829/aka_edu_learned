all: server server_epoll

server: web.c
	gcc web.c -o server

server_epoll: web_epoll.c
	gcc web_epoll.c -o server_epoll
