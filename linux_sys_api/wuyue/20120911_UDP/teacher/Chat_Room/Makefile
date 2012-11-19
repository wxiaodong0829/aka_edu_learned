all: server client

server: chat_room.c
	gcc chat_room.c -o server -g -DDEBUG
client: client.c
	gcc client.c -o client -g
clean:
	rm server client
.PHONY: clean
