#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <ctype.h>

#define SERV_PORT 8000
#define SERV_IP "127.0.0.1"

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int is_ip(const char *file)
{
	if(file[0] >= '0' && file[0] <= '9')
		return 1; // 是ip地址
	else 
		return 0; // 是目录
}

int main(void)
{
	int sfd,cfd,n;
	char buf[1024];
	int fd;
	struct sockaddr_in serv_addr;

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,SERV_IP,&(serv_addr.sin_addr.s_addr));

	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
		err_sys("socket error");

	n = bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");

	n = listen(sfd,20);
	if(n == -1)
		err_sys("listen error");

	while(1)
	{
		cfd = accept(sfd,NULL,NULL);
		if(cfd == -1)
			err_sys("accept error");

		n = read(cfd,buf,1024);
		buf[n] = '\0';
		printf("%d: <%s>\n", __LINE__, buf);
		if(n == 0)
		{
			printf("connection closed...\n");
			return 0;
		}

		if(is_ip(buf) == 1)//上传文件
		{
			char *p, file[1024];
			p = index(buf, ':');
			printf("%s\n",p+1);
			strcpy(file, p+1);
			printf("%s\n",file);

			write(cfd, "OK", 2);

			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,0644);
			if(fd == -1)
				err_sys("open file error");
			while((n = read(cfd, buf, 1024)) != 0)
			{
				printf("%s\n", buf);
				write(fd,buf,n);
			}
		}
		else //下载文件
		{
			printf("%d: <%s>\n", __LINE__, buf);
			fd = open(buf, O_RDONLY);
			if(fd == -1)
				err_sys("open file1 error");
			while((n = read(fd,buf,1024))!=0)
				write(cfd,buf,n);
		}
		close(fd);
		close(cfd);
	}

	return 0;
}
