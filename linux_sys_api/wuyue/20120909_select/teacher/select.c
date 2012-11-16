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
#define SERV_PORT 8000

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
	fd_set allset, rset;

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

	for(i = 0; i < 1024; i++)
		clients[i] = -1;
	max_i = -1; max_fd = lfd;	
	FD_ZERO(&allset); FD_ZERO(&rset);
	FD_SET(lfd, &allset);

	while(1){
		char buf[1024];
		int nready, j, cfd;
		
		rset = allset;
		nready = select(max_fd + 1, &rset, 
			NULL, NULL, NULL);
		if(nready == -1)
			err_sys("select error");

		if(FD_ISSET(lfd, &rset)){
			cfd = accept(lfd, NULL, NULL);
			if(cfd == -1)
				err_sys("accept error");
			for(i = 0; i < 1024; i++)
				if(clients[i] == -1)
					break;
			if(i == 1024){
				printf("too many clients...\n");
				return 0;
			}
			clients[i] = cfd;
			if(i > max_i) max_i = i;
			if(cfd > max_fd) max_fd = cfd;
			FD_SET(cfd, &allset);

			if(--nready == 0)
				continue;
		}

		for(i = 0; i <= max_i; i++){
			cfd = clients[i];
			if(cfd == -1)
				continue;
			if(FD_ISSET(cfd, &rset)){
				n = read(cfd, buf, 1024);
				if(n == 0){
					close(cfd);
					clients[i] = -1;
					FD_CLR(cfd, &allset);
				}else{
					for(j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
					write(cfd, buf, n);
				}
			
				if(--nready == 0)
					break;
			}
		}

		printf("one round is over...\n");
	}

	printf("should not be here\n");

	return 0;
}
