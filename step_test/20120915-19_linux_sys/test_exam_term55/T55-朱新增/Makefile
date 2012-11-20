all: server client

server: serve.c
	gcc serve.c -o server
client: my_scp.c
	gcc my_scp.c -o client -g
clean:
	rm server client
