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
#include <signal.h>
#include <errno.h>
#include "err.h"

#define SERV_PORT 60000
#define SERV_ADDR "127.0.0.1"
#define IPSIZE 20


int main(int argc, char **argv)
{
	struct sockaddr_in serv_addr, cliaddr;
	int n, cli_len, i, j;
	char buf[BUFSIZ];
	char cli_str[IPSIZE];
	int sfd, cfd;
	int maxi, maxfd;
	fd_set allset, readset;
	int nready;
	int client[FD_SETSIZE];


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

	maxfd = sfd;			/* select init*/
	FD_ZERO(&allset);
	FD_SET(sfd, &allset);

	maxi = 0;				/* 存放 数据 套接字 数组   */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;
	while (1) {
		readset = allset;
		nready = select(maxfd + 1, &readset, NULL, NULL, NULL);
		if (nready == -1)
			error_sys("select");
		
		if (FD_ISSET(sfd, &readset)) {
			cli_len = sizeof(cliaddr);
			cfd = accept(sfd, (struct sockaddr *)&cliaddr, (socklen_t *)&cli_len);
			if (cfd == -1) {
				if ((errno == ECONNABORTED) || (errno == EINTR))
					continue;
				error_sys("accept");
			}
			printf("received from %s at port :%d\n", inet_ntop(AF_INET, 
						&cliaddr.sin_addr.s_addr, cli_str, IPSIZE), ntohs(cliaddr.sin_port));

			for (i = 0; i < maxi; i++) /* 维护 数据套接字 数组*/
				client[i] = cfd;
			if (i == maxi) {
				client[i + 1] = cfd;
				maxi = i + 1;
			}

			FD_SET(cfd, &allset); /* 维护 传入 select 中的位图集 */
			if (maxfd < cfd)
				maxfd = cfd;

			if (--nready <= 0)
				continue;
		}

		for (i = 0; i <= maxi; i++) { /* 执行到 这里，说明，有 可用 的数据套接字中有被检测的事件发生 */
			if (client[i] == -1)
				continue;
			if (FD_ISSET(client[i], &readset)) {
				n = read(client[i], buf, BUFSIZ);
				if (n == 0) { /* no data and client is closed */
					FD_CLR(client[i], &allset);
					close(client[i]);
					client[i] = -1;
				} else {
					for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
					write(client[i], buf, n);         /*  也需要检测是否可写，但为解释 select 工作原理，省略*/
				}
			}
			if (--nready <= 0)
				break;
		}

	}

	close(sfd);
	return 0;
}
