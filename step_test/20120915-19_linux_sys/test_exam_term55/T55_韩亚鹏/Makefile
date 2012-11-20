all: server client

server: server.c 
	gcc server.c  -o server -g -Wall
	
client: client.c 
	gcc client.c -o client -g -Wall
clean:
	rm server client
