/*************************************************************************
    > File Name: client.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月08日 星期六 18时03分47秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "err.h"

#define SERV_PORT 60000
#define SERV_ADDR "127.0.0.1"

int main(int argc, char **argv)
{
	struct sockaddr_in serv_addr;
	int cfd; int n;
	char buf[BUFSIZ];

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd == -1)
		error_sys("socket");

	memset(&serv_addr, 0, sizeof(serv_addr)); //用sizeof可使更通用
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_ADDR, &serv_addr.sin_addr.s_addr);

	n = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n == -1)
		error_sys("connect");

	while (1) {
		n = read(STDIN_FILENO, buf, BUFSIZ);
		if (n == 0) //手动产生文件结束符 ctrl + d
			break;
		n = write(cfd, buf, n);//将数据放到发送缓冲区中，此时write立即返回，不管是否已经发出去了，若对方已关闭链接，则无法发送，并将置RST标志位，表示对方已经关闭链接，当下一次调用write时，write启动另一个内核函数去检查到此标志位，然后向此客户端程序发送SIGPIPE信号，默认是终止进程，若是服务器，需将此信号的处理方式改为捕捉，不致服务器出现崩溃
		n = read(cfd, buf, BUFSIZ);
		n = write(STDOUT_FILENO, buf, n);
	}
	close(cfd);
	return 0;
}
