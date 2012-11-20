all: server client

server: server.c
	gcc server.c -o server -g
client: myscp.c
	gcc myscp.c -o client -g
clean:
	rm server client
.PHONY: clean
