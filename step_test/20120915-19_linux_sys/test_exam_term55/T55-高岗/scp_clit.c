#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//#define ROOT "./cli"
#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void my_err(const char *str)
{
	perror(str);
	exit(-1);
}

int main(int argc, char *argv[])
{
	int sfd, fd, n, len, flags;
	struct sockaddr_in serv_addr;
	char path[1024], buf[1024];

	if(argc != 3)
		printf("argc less...\n");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		my_err("socket error");

	connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	strcpy(buf, argv[1]);
	write(sfd, buf, sizeof(buf));

	sprintf(path, "%s/%s", argv[2], argv[1]);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	while(n = read(sfd, buf, 1024));
	write(fd, buf, n);

	close(fd);
	close(sfd);
	/*
	   strcpy(buf, argv[1]);
	   write(sfd, buf, sizeof(buf));

	   sprintf(path, "%s/%s", argv[2], argv[1]);
	   fd = open(path, O_RDONLY);
	   while(n = read(fd, buf, 1024))
	   write(sfd, buf, 1024);
	   close(sfd);
	*/
	return 0;
}
