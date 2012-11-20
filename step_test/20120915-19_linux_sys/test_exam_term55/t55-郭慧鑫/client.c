#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>

#define SERV_PORT 8000

void err_sys(char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in serv_addr;
	int sfd, cfd, fd;
	char buf[1024];
	char *filename, *name, *ip;
	char path[1024], *dir;
	int i, n;

	if(argc != 3)
		err_sys("argc");

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		err_sys("socket");

	name = strstr(argv[1], ":");
	if(name == NULL){/* 上传文件 */

		name = argv[1];
		filename  = rindex(argv[1], '/') + 1;
		dir = strstr(argv[2], ":") + 1;
		ip = argv[2];

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

		cfd = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(cfd == -1)
			err_sys("connect error");

		write(sfd, dir, strlen(dir) + 1);
		read(sfd, buf, 1024);
		write(sfd, filename, strlen(filename) + 1);
		read(sfd, buf, 1024);

		n = access(name, F_OK);//上传文件是否存在
		if(n == -1){
			printf("no this file\n");
			close(sfd);
			return 0;
		}else{
			fd = open(name, O_RDONLY);
			if(fd == -1)
				err_sys("open error");

			while(n = read(fd, buf, 1024))
				write(sfd, buf, n);

			close(sfd);
		}
	}
	else{/* 下载文件*/
		dir = argv[2];
		filename = strstr(argv[1], ":") + 1;
		name = rindex(filename, '/') + 1;
		ip = argv[1];


		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

		cfd = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(cfd == -1)
			err_sys("connect error");


		write(sfd, filename, strlen(filename) + 1);

		sprintf(path, "%s/%s", dir, name);
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd == -1)
			err_sys("open error");

		while(n = read(sfd, buf, 1024))
			write(fd, buf, n);

		close(fd);
	}

	close(sfd);
	return 0;
}

