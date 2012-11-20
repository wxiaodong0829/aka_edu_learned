#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void err_sys(char *str)
{
	perror(str);
	exit(1);
}
int main(int argc, char *argv[])
{
	int sfd, fd, n;	
	char buf[1024], path[1024];
	char *p, *q, *filename, *ip, *dir, *name;
	struct sockaddr_in serv_addr;
	
	p = strstr(argv[1], ":");
	if(p == NULL){ /*上传文件*/
		filename = argv[1];
		q = rindex(argv[1], '/');
		name = q + 1;
		p = strstr(argv[2], ":");
		*p = '\0';
		ip = argv[2];
		dir = p + 1;

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(8000);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

		sfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sfd == -1)
			err_sys("socket error");
		
		n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(n == -1)
			err_sys("connect error");

		write(sfd, dir, strlen(dir) + 1);

		n = read(sfd, buf, 1024);
		if(n == -1)
			err_sys("read error");

		write(sfd, name, strlen(name) + 1);
		n = read(sfd, buf, 1024);
		if(n == -1)
			err_sys("read error");
		
		fd = open(filename, O_RDONLY);
		if(fd == -1)
			err_sys("open error");
		
		while(n = read(fd, buf, 1024))
			write(sfd, buf, n);

		close(fd);
	}else{ /*下载文件*/
		
		dir = argv[2];
		strcpy(buf, argv[1]);
		p = strstr(argv[1], ":");
		*p = '\0';
		ip = argv[1];
		filename = p + 1; 
		
		p = rindex(buf, '/');
		name = p + 1;

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(8000);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

		sfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sfd == -1)
			err_sys("socket error");

		n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(n == -1)
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
