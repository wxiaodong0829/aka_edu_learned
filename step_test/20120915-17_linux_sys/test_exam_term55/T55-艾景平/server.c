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

int main(void)
{
	int lfd, cfd, i, n;
	struct sockaddr_in serv_addr;

	lfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		sys_err("bind error");
	listen(lfd, 20);

	while(1){
		cfd = accept(lfd, NULL, NULL);
		if(cfd ==-1)
			sys_err("accept error");
		char buf[1024], path[1024],tmp[1024];
		int fd;
		char *p,*q;
		char *filename;

		n = read(cfd, buf, 1024);
		buf[n] = '\0';
		strcpy(tmp,buf);
#if 1
		p = strstr(buf,":");
		if(p != NULL)
		{      /*download file from server*/
			filename = p+2;
#endif
			sprintf(path, "/%s",filename);

			fd = open(path, O_RDONLY);
			if(fd == -1)
				exit(1);
			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);
			close(cfd);
		}
		else
		{      /*upload file to server*/
			write(cfd,"ok",3);
			q = rindex(tmp,'/');

			n = read(cfd,buf,1024);
			buf[n] = '\0';
			sprintf(path,"%s%s",buf,q);
		//	printf("path:%s\n",path);

			write(cfd,"ok",3);

			fd = open(path,O_WRONLY | O_CREAT | O_TRUNC ,0644);
			if(fd == -1)
			{
				sys_err("open error");
			}
			while(n = read(cfd,buf,1024))
				write(fd,buf,n);

			close(cfd);
			close(fd);
		}
	}
	return 0;
}
