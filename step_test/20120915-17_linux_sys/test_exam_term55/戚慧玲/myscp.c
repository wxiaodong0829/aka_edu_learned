#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define SERV_PORT 8000
#define SERV_IP "127.0.0.1"

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int dir_or_ip(char *file)
{
	if(file[0] >= '0' && file[0] <= '9')
		return 1; // 是ip地址
	else 
		return 0; // 是目录
}

int main(int argc,const char *argv[])
{
	int lfd,n;
	int fd;
	struct sockaddr_in serv_addr;
	char buf[1024];

	if(argc != 3)
		err_sys("wrong");

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,SERV_IP,&(serv_addr.sin_addr.s_addr));

	lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1)
		err_sys("socket error");

	n = connect(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(n == -1)
		err_sys("connection error");

	strcpy(buf, argv[1]);

	printf("%d\n", dir_or_ip(buf));	//是目录，向服务器端传文件
	if(dir_or_ip(buf) == 0)	//是目录，向服务器端传文件
	{
		char filename[1024];
		char *p;
		char name[1024];

		p = rindex(argv[1], '/');
		strcpy(name, p+1);
		printf("%s\n", name);
		sprintf(filename,"%s/%s",argv[2],name);
		printf("%s\n",filename);

		write(lfd,filename,strlen(filename)+1);

		read(lfd, buf, 1024);	/* 清空缓冲区，把两次write分开 */

		int fd = open(argv[1],O_RDONLY);
		if(fd == -1)
			err_sys("open file2 error");

		while((n = read(fd, buf,1024))!=0)
			write(lfd,buf,n);
	}
	else if(dir_or_ip(buf) == 1) //是ip，从服务器上面下载文件到客户端
	{
		char *p, filename[1024], serv_path[1024];
		char name[1024];

		p = index(argv[1], ':');
		strcpy(serv_path, p+1);
		write(lfd,serv_path,strlen(serv_path)+1);//将发给服务器,str[1]存放要下摘的文件的路径

		p = rindex(argv[1], '/');
		strcpy(filename, p+1);
		sprintf(name, "%s/%s",argv[2], filename);
		printf("%s\n", name);

		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if(fd == -1)
			err_sys("open error");
		while((n = read(lfd,buf,1024)) != 0)
		{
			printf("%s\n", buf);
			write(fd,buf,n);
		}
	}
	close(lfd);
	close(fd);

	return 0;
}
