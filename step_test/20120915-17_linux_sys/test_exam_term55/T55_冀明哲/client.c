#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void sys_error(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sfd, fd, n;
	char buf[1024];
	char path[1024];
	struct sockaddr_in serv_addr;

	if(argc != 3)
	{
		sys_error("input error");
	}

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd = -1)
		sys_error("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n < 0)
		sys_error("connect error");

	while(1)
	{
		if(strstr(argv[1], ":"))//download
		{
			char *p;
#if 0
			int i;
			struct stat *buf1;

			i = stat(argv[1], buf1);
			if(i = -1)
				sys_error("stat error");
#endif

			sprintf(path, "%s", argv[1]);
			write(sfd, path, sizeof(path));
			p = rindex(argv[1], '/');
			p = p + 1;
			sprintf(path, "%s/%s", argv[2], p);

			fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if(fd < 0)
				sys_error("open failed");

			while(n = read(sfd, buf, 1024))
				write(fd, buf, n);


			break;

		}
		else //upload
		{
			sprintf(path, "%s %s", argv[1], argv[2]);
			write(sfd, path, sizeof(path));

			fd = open(argv[1], O_RDONLY);
			if(fd < 0)
				sys_error("open failed");

			while(n = read(fd, buf, 1024))
				write(sfd, buf, n);

			break;

		}
	}

	close(fd);
	close(sfd);

	return 0;
}

