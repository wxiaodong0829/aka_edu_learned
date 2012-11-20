#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(char *str)
{
	perror(str);
	exit(1);
}
int main(void)
{
	struct sockaddr_in serv_addr;
	int sfd, cfd, n;
	char buf[1024], path[1024];
	char *dir;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");

	n = listen(sfd, 20);
	if(n == -1)
		err_sys("listen error");

	struct stat stat_buf;
	while(1)
	{
		char path[1024];
		int fd;

		cfd = accept(sfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept error");

			n = read(cfd, buf, 1024);
			if(n == -1)
				err_sys("read error");
			buf[n] = '\0';

			n = stat(buf, &stat_buf);
			if(n == -1)
				err_sys("stat error");

			if(S_ISREG(stat_buf.st_mode)){//下载文件
				fd = open(buf, O_RDONLY);
				if(fd == -1)
					err_sys("server open error");

				while((n = read(fd, buf, 1024)) != 0)
					write(cfd, buf, n);

				close(fd);
				close(cfd);
			}
			if(S_ISDIR(stat_buf.st_mode)){//下载文件
				int fd, len = strlen(buf);
				
				dir = (char *)malloc(len + 1);
				strcpy(dir, buf);

			  write(cfd, "ok", 3);

				n = read(cfd, buf, 1024);
				if(n == -1)
					err_sys("read error");
				buf[n] = '\0';

				write(cfd, "ok", 3);
				sprintf(path, "%s/%s", dir, buf);

				fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(fd == -1)
					err_sys("open error");

				while(n = read(cfd, buf, 1024))
					write(fd, buf, n);
				printf("over...\n");
				
				close(fd);
				close(cfd);
			}
	}
	return 0;
}
