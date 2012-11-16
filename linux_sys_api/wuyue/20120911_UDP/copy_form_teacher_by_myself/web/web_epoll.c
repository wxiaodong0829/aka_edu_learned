/*************************************************************************
    > File Name: web.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月11日 星期二 22时34分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000
#define ROOT "./www"

#define REPLY_HEAD "HTTP/1.1 200 OK\r\nContent-Type:"
#define TEXT "text/html"
#define IMG "image/jpg"
#define REPLY_END "\r\n\r\n"

#define STAT_INIT		0
#define STAT_HTTP_HEAD  1
#define STAT_DATA	    2


void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int sock_init()
{
	int lfd;
	struct sockaddr_in serv_addr;
	int n;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n == -1)
		err_sys("bind error");
	n = listen(lfd, 20);
	if (n == -1)
		err_sys("listen error");

	return lfd;
}
typedef struct link {
	char *filename;
	int cfd;
	int attr;		/* attribute, 此次请求的类型 cgi  or not */
	char * type;	/* 传输的文件的格式 字符串地址 */
	int status;		/* 描述此链接传输的过程： 0，初始态  1，协议头	2，真正的数据*/
} link_t;
int main(void)
{
	int lfd, cfd;
	struct sockaddr_in serv_addr;
	char buf[1024];
	int n;
	struct epoll_event ep;
	struct epoll_event events[FD_SETSIZE];
	int efd;
	int res;
	int i, nread, nready;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n == -1)
		err_sys("bind error");
	n = listen(lfd, 20);
	if (n == -1)
		err_sys("listen error");
	efd = epoll_create(FD_SETSIZE);
	if (efd == -1)
		err_sys("epoll_create");
	ep.events = EPOLLIN, ep.data.fd = lfd;
	res = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ep);
	if (res == -1)
		err_sys("epoll_ctl 1");

	while (1) {
		char path[1024];
		char *p, *q, *filename, *type;
		int fd;

		nready = epoll_wait(efd, (struct epoll_event *)&events, FD_SETSIZE, -1);
		if (nready == -1)
			err_sys("epoll_wait");
		for (i = 0; i < nready; i++) {
//			if (events[i].events == EPOLLIN) {
				if (events[i].data.fd == lfd) { /* 链接请求*/
					cfd = accept(lfd, NULL, NULL);
					if (cfd == -1)
						err_sys("accept");
					ep.events = EPOLLIN, ep.data.fd = cfd;
					res = epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ep);
					if (res == -1)
						err_sys("epoll_ctl 2");
				} else {						/* 普通数据*/
					int sfd;
					sfd = events[i].data.fd;

					nread = read(sfd, buf, 1024);
					close(sfd);

					write(STDOUT_FILENO, buf, nread);
				}
//			} else if (events[i].events == EPOLLIN) {
//			} else if (events[i].events == EPOLLIN) {
//			}
		}
	}
#if 0
		cfd = accept(lfd, NULL, NULL);
		if (cfd == -1)
			err_sys("accept error");
		
		n = read(cfd, buf, 1024);
		buf[n] = '\0';

		p = strstr(buf, " ");
		q = strstr(p + 1, " ");
		*q = '\0';
		filename = p + 2;
		sprintf(path, "%s/%s", ROOT, filename);

		n = access(path, X_OK);
		if (n == 0) { /* cgi */
			pid_t pid;
			char *argv[2];

			write(cfd, REPLY_HEAD, strlen(REPLY_HEAD));
			write(cfd, TEXT, strlen(TEXT));
			write(cfd, REPLY_END, strlen(REPLY_END));

			pid = fork();
			if (pid == 0) {
				dup2(cfd, STDOUT_FILENO);
				argv[0] = path, argv[1] = NULL;
				execvp(path, argv);
				err_sys("exec error");
			} else {
				close(cfd);
				wait(NULL);
			}
		} else { /* 普通网页数据请求  */
			p = rindex(filename, '.');
			if (strcmp(p + 1, "jpg") == 0)
				type = IMG;
			else
				type = TEXT;

			fd = open(path, O_RDONLY);
			if (fd != -1) {
				write(cfd, REPLY_HEAD, strlen(REPLY_HEAD));
				write(cfd, type, strlen(type));
				write(cfd, REPLY_END, strlen(REPLY_END));

				while (n = read(fd, buf, 1024))
					write(cfd, buf, n);
				close(fd);
			}

			close(cfd);
		}
	}
#endif

	return 0;
}
