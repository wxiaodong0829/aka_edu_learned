/*************************************************************************
    > File Name: mmap.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月21日 星期二 11时49分38秒
 ************************************************************************/

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int *p;
	int fd = open("hello", O_RDWR);

	if (fd < 0) {
		perror("open hello: ");
		exit(1);
	}
	p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap: ");
		exit(1);
	}

	close(fd);

	p[0] = 0x30313233;

	munmap(p, 6);

	return 0;
}
