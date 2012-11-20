#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	char *filename,*dirname,*dirname1;
	int fd,sfd;
	int res,n;
	int len,len1;
	char buf[1024];
	struct sockaddr_in serv_addr;

	len = strlen(argv[1]);
	filename = (char *)malloc(len);
	filename = argv[1];

	len1 = strlen(argv[2]);
	dirname = (char *)malloc(len1);
	dirname = argv[2];

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);

	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0)
		sys_err("socket error");

	res = connect(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(res == -1)
		sys_err("connect error");
	else
	{
		char path[1024];
		char *p,*q,*tmp;

		write(sfd,filename,strlen(filename));

		tmp = strstr(filename,":");
		if(tmp != NULL)    /*download file1 from server*/
		{
			p = rindex(filename,'/');
			q = p+1;

			sprintf(path,"%s/%s",argv[2],q);
			fd = open(path,O_WRONLY | O_CREAT | O_TRUNC,0644);
			if(fd == -1)
				sys_err("open error");
			while(n = read(sfd,buf,1024))
				write(fd,buf,n);
			printf("download finished...\n");
			close(fd);
		}
		else
		{                 /*upload file to server*/
		        read(sfd,buf,1024);
			p = strstr(dirname,":");
			q = p+1;
			len1 = strlen(q);
			dirname1 = (char *)malloc(len1);
			dirname1 = q;
		
			write(sfd,dirname1,strlen(dirname1));
			read(sfd,buf,1024);

			fd = open(argv[1],O_RDONLY);
			if(fd < 0)
				sys_err("open error");

			while(n = read(fd,buf,1024))
				write(sfd,buf,n);
			printf("upload successfully...\n");
			close(fd);
		}
			close(sfd);
	}
	return 0;
}
