#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

//#define SERV_IP "192.168.204.112"
#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int lfd, efd;
	struct sockaddr_in serv_addr;
	int n, i;
	struct epoll_event ep;
	struct epoll_event events[FD_SETSIZE];

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
	if(efd == -1)
		err_sys("epoll_create error");
	ep.events = EPOLLIN; ep.data.fd = lfd;	
	epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ep);

	while(1){
		char buf[1024];
		int nready, j, cfd;
	
		nready = epoll_wait(efd, events, FD_SETSIZE, -1);
		for(i = 0; i < nready; i++){
			if(events[i].events == EPOLLIN){
				if(events[i].data.fd == lfd){ /* lfd */
					cfd = accept(lfd, NULL, NULL);
					if(cfd == -1)
						err_sys("accept error");			
					
					ep.data.fd = cfd; ep.events = EPOLLIN;
					epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ep);
				}else{ /* cfd */
					cfd = events[i].data.fd;
					n = read(cfd, buf, 1024);
					if(n == 0){
						epoll_ctl(efd, EPOLL_CTL_DEL, cfd, NULL);

						close(cfd);
					}else{
						for(j = 0; j < n; j++)
							buf[j] = toupper(buf[j]);
						write(cfd, buf, n);
					}
				}
			}else
				printf("impossable...\n");
		}
		
		printf("one round is over...\n");
	}

	close(efd);
	close(lfd);
	printf("should not be here\n");

	return 0;
}
