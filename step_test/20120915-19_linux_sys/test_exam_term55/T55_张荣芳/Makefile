all: server myscp 

server: myscp_server.c
	gcc -g -Wall myscp_server.c -o server -DDEBUG

myscp : myscp_client.c
	gcc -g -Wall myscp_client.c -o myscp -DDEBUG

clean:
	rm server myscp file2 file1

.PHONY: clean
