#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000
#define ROOT "./www"

#define REPLY_HEAD "HTTP/1.1 200 OK\r\nContent-Type:"
#define TEXT "text/html"
#define IMG "image/jpg"
#define REPLY_END "\r\n\r\n"

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int lfd, cfd;
	struct sockaddr_in serv_addr;
	char buf[1024];
	int n;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		err_sys("socket error");

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
		char path[1024]; 
		char *p, *q, *filename, *type;
		int fd;

		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept error");
	
		n = read(cfd, buf, 1024);
		buf[n] = '\0';

		p = strstr(buf, " ");
		q = strstr(p + 1, " ");
		*q = '\0';
		filename = p + 2;
		sprintf(path, "%s/%s", ROOT, filename);

		n = access(path, X_OK);
		if(n == 0){ /* cgi */
			pid_t pid;
			char *argv[2];

			write(cfd, REPLY_HEAD, strlen(REPLY_HEAD));
			write(cfd, TEXT, strlen(TEXT));
			write(cfd, REPLY_END, strlen(REPLY_END));
			
			pid = fork();
			if(pid == 0){
				dup2(cfd, STDOUT_FILENO);
				argv[0] = path, argv[1] = NULL;
				execvp(path, argv);
				err_sys("exec error");
			}else{
				close(cfd);
				wait(NULL);
			}
		}else{
			p = rindex(filename, '.');
			if(strcmp(p + 1, "jpg") == 0)
				type = IMG;
			else
				type = TEXT;

			fd = open(path, O_RDONLY);
			if(fd != -1){
				write(cfd, REPLY_HEAD, strlen(REPLY_HEAD));
				write(cfd, type, strlen(type));
				write(cfd, REPLY_END, strlen(REPLY_END));

				while(n = read(fd, buf, 1024))
					write(cfd, buf, n);
				close(fd);
			}
			
			close(cfd);
		}
	}

	return 0;
}
