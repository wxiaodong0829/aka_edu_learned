/*************************************************************************
    > File Name: server.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月08日 星期六 17时00分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include "err.h"

#define SERV_PORT 60000
#define SERV_ADDR "127.0.0.1"
#define IPSIZE 20

void *pth(void *arg)
{
	int cfd = (int)arg;
	int n, i;
	char buf[BUFSIZ];
	while (1) {
		n = read(cfd, buf, BUFSIZ);//只有当数据结束时才跳出，去关闭链接cfd
		//close(cfd);
//		shutdown(cfd, SHUT_WR);
	//	printf("i can still received: %s\n", buf);
		if (n == 0) {
			write(STDOUT_FILENO, "connect close...\n", 17);
			break;
		}

		for (i = 0; i < n; i++)
			buf[i] = toupper(buf[i]);
		n = write(cfd, buf, n);
	}
	close(cfd);
	return NULL;
}
int main(int argc, char **argv)
{
	struct sockaddr_in serv_addr, cliaddr;
	int sfd, cfd;
	int n, cli_len;
	char cli_str[IPSIZE];
	pthread_t tid;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
		error_sys("socket");

	memset(&serv_addr, 0, sizeof(serv_addr)); //用sizeof可使更通用
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_ADDR, (void *)&serv_addr.sin_addr.s_addr);

	n = bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n == -1)
		error_sys("bind");

	n = listen(sfd, 20);
	if (n == -1)
		error_sys("listen");

	while (1) {
		cli_len = sizeof(cliaddr);
		cfd = accept(sfd, (struct sockaddr *)&cliaddr, (socklen_t *)&cli_len);
		if (cfd == -1) {
			if ((errno == ECONNABORTED) || (errno == EINTR))
				continue;
			error_sys("accept");
		}
		printf("received from %s at port :%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cli_str, IPSIZE), ntohs(cliaddr.sin_port));

		n = pthread_create(&tid, NULL, pth, (void *)cfd);
		if (n != 0)
			perror("n");
		pthread_detach(tid);
		
	}
	close(sfd);
	return 0;
}
