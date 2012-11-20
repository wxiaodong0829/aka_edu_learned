all: server myscp 

server: server.c
	gcc server.c -o server -g

myscp: client.c
	gcc client.c -o client -g

clean:
	rm server client 

.PHONY: clean
