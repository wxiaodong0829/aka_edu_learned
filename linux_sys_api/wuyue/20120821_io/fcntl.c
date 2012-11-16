/*************************************************************************
    > File Name: fcntl.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月21日 星期二 10时06分21秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int flags;
	int n;
	char buf[BUFSIZ];

	flags = fcntl(0, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(0, F_SETFL, flags);
#if 0
again:
	n = read(0, buf, BUFSIZ);
	if (n == -1) {
		if (errno == EWOULDBLOCK) {
			printf("no data ...\n");
			sleep(3);
			goto again;
		} else
			return -1;
	}
#endif
	while((n = read(0, buf, BUFSIZ)) == -1)
		if (errno == EWOULDBLOCK) {
			printf("no data ...\n");
			sleep(3);
		}
	write(1, buf, n);
	return 0;
}
