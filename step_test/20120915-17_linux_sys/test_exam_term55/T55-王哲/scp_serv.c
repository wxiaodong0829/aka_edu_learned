#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 8000
#define SERV_IP "127.0.0.1"
#define ROOT "./serv"

void my_err(const char *str)
{
	perror(str);
	exit(1);
}
int main(void)
{
	int lfd, cfd, fd, i, n;
	struct sockaddr_in serv_addr;
	struct sigaction act;
	char  buf[1024], path[1024];

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		my_err("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(lfd, 10);

	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGCHLD, &act, NULL);

	while(1)
	{
		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1 )
			my_err("accept error");
		while(1)
		{
			n = read(cfd, buf, 1024);
			if(n == 0)
				break;

			sprintf(path, "%s/%s", ROOT, buf);
			fd = open(path, O_RDONLY);

			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);

			close(fd);
		}
			close(cfd);
	}
		return 0;
}
