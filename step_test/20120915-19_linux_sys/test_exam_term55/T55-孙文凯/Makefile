all: server myscp

server: myscp_server.c err.c myscp.h
	gcc myscp_server.c err.c myscp.h -o server -g -Wall
myscp: myscp_client.c match.c err.c myscp.h
	gcc myscp_client.c match.c err.c myscp.h -o myscp -g -Wall
clean:
	rm server myscp
.PHONY: clean
