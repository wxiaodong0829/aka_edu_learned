#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000
void err_sys(const char *str)
{
	perror(str);
	exit(0);
}

int main(void)
{
	int lfd, cfd;
	int fd;
	struct sockaddr_in serv_addr;
	struct sigaction act;
	char buf[1024], path[1024], filename[255];
	int n;

	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;	
	sigaction(SIGCHLD, &act, NULL);

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		err_sys("socket error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");

	n = listen(lfd, 20);
	if(n == -1)
		err_sys("listen error");

	while(1)
	{
		char *p;
		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept error");
		n = read(cfd, buf, 1024);	
		if(n == -1)
			err_sys("read error");
		buf[n] = '\0';
		p = buf;
		strcpy(path, p+1);
		printf("%s\n", path);
		if(buf[0] == 'L')
		{
			printf("客户要下载文件\n");
			fd = open(path, O_RDONLY);
			if(fd == -1)
			err_sys("server open error");
			while(n =read(fd, buf, 1024))
				write(cfd, buf, n);
			printf("下载完成\n");
			close(fd);	
			close(cfd);
		}
		else if(buf[0] == 'S')
		{
			printf("客户端要上传文件\n");
			if(n == -1)
				err_sys("read error");
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd == -1)
			err_sys("open error");
			while(n = read(cfd, buf, 1024))
				write(fd, buf, n);
			close(fd);
			close(cfd);
			printf("上传文件结束\n");
		}
	}
	return 0;
}

