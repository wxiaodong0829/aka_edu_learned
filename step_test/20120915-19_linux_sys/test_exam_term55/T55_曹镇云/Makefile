all:./server/server myscp

server: ./server/server.c
	gcc ./server/server.c -o server -g
myscp: client.c
	gcc client.c -o myscp -g
clean:
	rm ./server/server myscp 

