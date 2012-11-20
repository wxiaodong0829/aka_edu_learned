#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>

sys_error(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int lfd, cfd, i, n;
	char buf[1024], path[1024];
	struct sockaddr_in serv_addr;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd < 0)
		sys_error("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	i = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(i < 0)
		sys_error("bind error");

	i = listen(lfd, 20);
	if(i < 0)
		sys_error("listen error");

	while(1)
	{
		char *p, *q;
		int fd;

		cfd = accept(lfd, NULL, NULL);
		
		n = read(cfd, buf, 1024);
		if(n < 0)
			sys_error("read failed");

		buf[n] = '\0';
		p = buf;
		if((q = strstr(buf, " ")) != NULL)//upload;
		{
			*q = '\0';
			q = q + 1;
			q = strstr(q, ":");
			q = q + 1;
			p = rindex(p, '/');
			p = p + 1;
			sprintf(path, "%s/%s", q, p);
			fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if(fd < 0)
				sys_error("open failed");
			while(n = read(cfd, buf, 1024))
				write(fd, buf, n);

			close(cfd);
			close(fd);
		}
		else //download;
		{
			q = strstr(buf, ":");
			q = q + 1;
			sprintf(path, "%s", q);

			fd = open(path, O_RDONLY);
			if(fd < 0)
				sys_error("open failed");

			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);

			close(cfd);
			close(fd);
		}
	}

	return 0;
}
