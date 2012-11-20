#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#define SERV_IP "192.168.204.103"
#define SERV_PORT 7000
#define N 1024
#define  ROOT "./pub"
#define CURDIR "."

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main()
{
	struct sockaddr_in servaddr;
	int lfd, cfd,n;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		err_sys("socket failed");

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr.s_addr);

	n =bind(lfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (n == -1)
		err_sys("bind failed");
	n = listen(lfd , 20);
	if(n == -1)
		err_sys("bind failed");

	printf("begin accepting...\n");

	while(1)
	{
		char buf[N],path[N];
		char *buf1;
		int fd;

		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept failed");

		n = read(cfd, buf, 1024);
		buf[n] = '\0';
		puts(buf);
		buf1 =buf;
		buf1++;
		puts(buf1);

		if(buf[0] == 'd')
		{
			sprintf(path, "%s/%s",ROOT, buf1);
			fd = open(path, O_RDONLY);
			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);
			close(fd);

			//close(cfd);
		}

		if(buf[0] == 'u')
		{
			int cur_fd;
			char curdir[N];
			write(cfd,"upload",strlen("upload"));

			//sprintf(curdir, "%s/%s",CURDIR, buf1);

			//cur_fd = open(curdir, O_WRONLY |O_CREAT | O_TRUNC, 0644);
			cur_fd = open(buf1, O_WRONLY |O_CREAT | O_TRUNC, 0644);
			while(n =read(cfd, buf, 1024))
			write(cur_fd, buf, n);

			printf("over....\n");
			close(cur_fd);
			//close(cfd);
		}
		close(cfd);
	}


		return 0;
	}
