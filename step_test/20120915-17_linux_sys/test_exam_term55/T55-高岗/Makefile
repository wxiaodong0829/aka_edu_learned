all: server client

server:scp_serv.c 
	gcc scp_serv.c -o server
client:scp_clit.c 
	gcc scp_clit.c -o client -g
clean:
	rm server client
