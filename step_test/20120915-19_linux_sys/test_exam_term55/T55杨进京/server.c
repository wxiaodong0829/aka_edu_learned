#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}
int main(void)
{
	int lfd, cfd, n;
	int fd;
	struct sockaddr_in serv_addr;
	lfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");
	n = listen(lfd, 20);
	if(n == -1)
		err_sys("listen error");

	while(1){
			char buf[1024], path[1024];
			cfd = accept(lfd, NULL, NULL);
			if(cfd == -1)
				err_sys("accept error");
			n = read(cfd, buf, 1024);
			buf[n] = '\0';
			sprintf(path, "%s", buf);
			fd = open(path, O_RDONLY);
			if(fd < 0)
				err_sys("open file error");

			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);
			close(cfd);
	}
}
