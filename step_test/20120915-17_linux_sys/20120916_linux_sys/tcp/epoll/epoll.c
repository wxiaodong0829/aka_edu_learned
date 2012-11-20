#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

//#define SERV_IP "192.168.204.112"
#define SERV_IP "127.0.0.1"
#define SERV_PORT 60000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int lfd;
	struct sockaddr_in serv_addr;
	int n, i;
	int clients[1024];
	int max_i, max_fd;
	struct epoll_event ep;
	struct epoll_event event[FD_SETSIZE];
	int efd;

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

	efd = epoll_create(FD_SETSIZE);
	if (efd == -1)
		error_sys("epoll_create");

	ep.events = EPOLLIN; ep.data.fd = lfd;
	n = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ep);
	if (n == -1)
		error_sys("epoll_ctl");


	while(1){
		char buf[1024];
		int nready, j, cfd;
		
		nready = epoll_wait(efd, events, FD_SETSIZE, -1);
		if(nready == -1)
			err_sys("select error");

		for (i = 0; i < nready; i++) {
			if (events[i].data.fd == lfd) { /* 监听套接字可用 , 创立链接，并注册到监听器 */
				cfd = accept(lfd, NULL, NULL);
				if (cfd == -1)
					error_sys("accept");

				ep.events = EPOLLIN; ep.data.fd = cfd;
				n = epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ep);
				if (n == -1)
					error_sys("epoll_ctl");

			} else { /* 普通套接字 可用 */
				int cfd = events[i].data.fd;
				if ((n = read(cfd, buf, BUFSIZ)) == 0) {
					close(cfd);

					ep.events = EPOLLIN; ep.data.fd = cfd;
					epoll_ctl(efd, EPOLL_CTL_DEL, cfd, &ep);
				} else { /* 正常读写  */
					for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
					write(cfd, buf, n);
				}
			}

		}

	}

	close(lfd);
	printf("should not be here\n");

	return 0;
}
