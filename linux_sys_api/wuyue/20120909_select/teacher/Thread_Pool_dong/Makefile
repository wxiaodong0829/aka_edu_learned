all: server client

server: thread.c
	gcc thread.c -o server -lpthread
client: client.c
	gcc client.c -o client
clean:
	rm server client
