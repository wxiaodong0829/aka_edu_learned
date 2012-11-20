#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ROOT "./serv"

int main(void)
{
	int lfd, cfd, i, n;
	char buf[1024], path[1024];
	struct sockaddr_in serv_addr;

	lfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	listen(lfd, 20);

	while(1) {
		char *p, *q;
		int fd;

		cfd = accept(lfd, NULL, NULL);
		n = read(cfd, buf, 1024);
		buf[n] = '\0';
		p = buf;
		if((q = strstr(buf, " ")) != NULL){
			*q = '\0';
			q = strstr(q + 1, ":");
			p = rindex(p, '/');
			p = p + 1;
			sprintf(path, "%s/%s", q, p);
			fd = open(path, O_WRONLY|O_TRUNC, 0644);
			while(n = read(cfd, buf, 1024))
				write(fd, buf, n);

			close(cfd);
			close(fd);
		}
		else{
			q = strstr(buf, ":");
			q = q + 1;
			sprintf(path, "%s", q);
			fd = open(path, O_RDONLY);
			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);

			close(cfd);
			close(fd);
		}
	}
	return 0;
}
