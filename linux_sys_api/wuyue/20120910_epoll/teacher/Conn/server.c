#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ROOT "./serv"

int main(void)
{
	int lfd, cfd, i, n;
	struct sockaddr_in serv_addr;
	pid_t pid;
	struct sigaction act;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	listen(lfd, 20);
			
	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGCHLD, &act, NULL);

	while(1){
		cfd = accept(lfd, NULL, NULL);
		pid = fork();
		if(pid == 0){
			char buf[1024], path[1024];
			int fd;

			close(lfd);
			n = read(cfd, buf, 1024);
			buf[n] = '\0';
			sprintf(path, "%s/%s", ROOT, buf);
			
			fd = open(path, O_RDONLY);
			while(n = read(fd, buf, 1024))
				write(cfd, buf, n);

			close(cfd);
			return 0;
		}

		close(cfd);
	}

	return 0;
}
