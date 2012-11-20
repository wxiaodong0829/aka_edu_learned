#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int lfd, cfd, i, n;
	struct sockaddr_in serv_addr;
	char buf[1024];
	pid_t pid;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1)
		err_sys("socket error");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n =bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n == -1)
		err_sys("bind error");
	n = listen(lfd, 20);
	if (n == -1)
		err_sys("listen error");
	while(1){
		char path[1024], *p, *q, *filename, *pathname;
		int fd;
		cfd = accept(lfd, NULL, NULL);
		if (cfd == -1)
			if (errno != ECONNABORTED && errno != EINTR)
				err_sys("accept error");

		n = read(cfd, buf, 1024);

		buf[n] = '\0';
		q = buf;

		if((p = strstr(buf, " ")) != NULL) {/*upload*/
			*p = '\0';
			filename =rindex(q, '/');
			pathname = strstr(p + 1, ":");
			sprintf(path, "%s/%s", pathname + 1, filename + 1);

			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd ==  -1)
				err_sys("open error");
			while (n = read(cfd, buf, 1024))
				write(fd, buf, n);

			close(fd);
			close(cfd);

		}else{// download
			pathname = strstr(buf, ":");
			sprintf(path, "%s", pathname + 1);

			fd = open(path, O_RDONLY);
			if (fd == -1)
				err_sys("open error");
			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);

			close(fd);
			close(cfd);
		}
	}

	return 0;
}
