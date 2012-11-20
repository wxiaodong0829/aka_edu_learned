#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void err_sys(const char *str){
	perror(str);
	exit(1);
}
void err_open(const char *str){
	perror(str);
}

int main(void)
{
	int lfd, cfd, i, n,fd,efd;
	char *p,*q;
	struct sockaddr_in serv_addr;
	struct epoll_event ep;
	struct epoll_event events[FD_SETSIZE];

	if((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	if(n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		err_sys("bind error");
	if((n = listen(lfd, 20)) < 0)
		err_sys("listen error");
	efd = epoll_create(FD_SETSIZE);
	ep.events = EPOLLIN;
	ep.data.fd = lfd;
	if((n = epoll_ctl(efd,EPOLL_CTL_ADD,lfd,&ep)) < 0)
		err_sys("epoll_ctl error");
	while(1){
		char buf[1024];
		int nready,j;
		nready = epoll_wait(efd,events,FD_SETSIZE,-1);
		for (j = 0; j < nready; j++){
			if(events[j].data.fd == lfd){
			again:
				cfd = accept(lfd, NULL, NULL);
				if(cfd == -1){
					if(errno == EINTR)
						goto again;
				else
					err_sys("accept error");
				}
				ep.events = EPOLLIN;
				ep.data.fd = cfd;
				if((n = epoll_ctl(efd,EPOLL_CTL_ADD,cfd,&ep)) < 0)
					err_sys("epoll_ctl error");
			}else{
				cfd = events[j].data.fd;	
				n = read(cfd,buf,1024);
				buf[n] = '\0';
				p = strchr(buf,' ');
				q =p;
				p = p + 1;
				*q = '\0';
				if(strcmp(buf,"up") == 0){
					if((fd = open(p,O_WRONLY | O_CREAT | O_TRUNC,0644)) < 0){
					epoll_ctl(efd,EPOLL_CTL_DEL,cfd,NULL);
					close(cfd);
					err_open("up open error");
					continue;
				}
					write(cfd,"ok",strlen("ok"));
					while((n = read(cfd,buf,1024)) != 0)
						write(fd, buf, n);
				}else if(strcmp(buf,"down") == 0){
					if((fd = open(p,O_RDONLY)) < 0){
						epoll_ctl(efd,EPOLL_CTL_DEL,cfd,NULL);
						close(cfd);
						err_open("down open error");
						continue;
					}
					write(cfd,"ok",strlen("ok"));
					while((n = read(fd,buf,1024)) != 0){
						write(cfd,buf,n);
					}		
				}
				epoll_ctl(efd,EPOLL_CTL_DEL,cfd,NULL);
				close(cfd);
				close(fd);
				printf("one client is over!\n");
			}
		}
	}
}
	
