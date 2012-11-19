all: server client

server: chat_room.c
	gcc -g chat_room.c -o server 

client: client.c
	gcc -g client.c -o client

clean: 
	rm server client

./PHONY: clean
