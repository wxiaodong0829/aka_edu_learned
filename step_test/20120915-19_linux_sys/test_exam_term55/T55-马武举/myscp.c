#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<fcntl.h>
#include<sys/socket.h>
#define ROOT "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sfd;
	char buf[1024], path[1024];
	int fd,n;
	char *p;
	struct sockaddr_in serv_addr;
	if(argc != 3)
	{
		printf("usage: ./myscp path path\n");
		exit(0);
	}
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, ROOT, &serv_addr.sin_addr.s_addr);

	n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("connect error");

	write(sfd, argv[1], strlen(argv[1]));
    p = rindex(argv[1],'/');
	
	fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd == -1)
		err_sys("open file error");

	while(n = read(sfd, buf, 1024))
		write(fd, buf, n);

	close(sfd);

	return 0;


}
