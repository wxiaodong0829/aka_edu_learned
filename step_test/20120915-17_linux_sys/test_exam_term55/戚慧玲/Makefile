all: server myscp

server: server.c
	gcc server.c -o server -g -Wall
myscp: myscp.c
	gcc myscp.c -o myscp -g -Wall

clean:
	rm server myscp

.PHONY: clean
