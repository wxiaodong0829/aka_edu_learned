#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "192.168.204.102"
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

	pause();

	while(1){
		int cfd, i;
		char buf[1024];

		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept error");

		while(1){
			n = read(cfd, buf, 1024);
			if(n == 0){
				printf("connection closed...\n");
				break;
			}
			for(i = 0; i < n; i++)
				buf[i] = toupper(buf[i]);
			write(cfd, buf, n);
		}

		close(cfd);
	}
	
	printf("should not be here\n");

	return 0;
}
