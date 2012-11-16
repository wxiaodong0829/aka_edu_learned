all: server client

#server: thread.c
#	gcc thread.c -o server -lpthread
server: server.c err.c err.h
	gcc server.c err.c -o server -lpthread
client: client.c
	gcc client.c -o client
clean:
	rm server client
