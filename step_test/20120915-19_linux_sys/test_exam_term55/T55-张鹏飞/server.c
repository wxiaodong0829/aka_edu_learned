#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(-1);
}
int main (void)
{
	int lfd, cfd, fd, n;
	struct sockaddr_in serv_addr;
	char buf[1024], buf_dir[1024], path[1024];
	struct stat buf_t;


	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr);

	n = bind(lfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");

	n = listen(lfd, 20);
	if(n == -1)
		err_sys("listen error");
	while(1)
	{
		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept error");

		n = read(cfd, buf, 1024);
		buf[n] = '\0';
	
		n = stat(buf, &buf_t);
		if(n == -1)
			err_sys("stat error");

		if(S_ISDIR(buf_t.st_mode))
		{
			if(buf[strlen(buf) - 1] == '/')
				buf[strlen(buf)-1] = '\0';
			strcpy(buf_dir, buf);
			n = read(cfd, buf, 1024);
			buf[n] = '\0';
			sprintf(path, "%s/%s", buf_dir, buf);

			fd = open (path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while(n = read(cfd, buf, 1024))
				write(fd, buf, n);
			close (fd);
			close (cfd);
		}

		else if(S_ISREG(buf_t.st_mode))
		{
			fd = open(buf, O_RDONLY);
			if(fd == -1)
				err_sys("open error");
			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);
			close (fd);
			close (cfd);		
		}
		else
		{
			printf("should not be here\n");
			close(cfd);
		}

	}

	return 0;
}
