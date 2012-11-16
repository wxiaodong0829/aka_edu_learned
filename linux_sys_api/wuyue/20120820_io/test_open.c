/*************************************************************************
    > File Name: test_open.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月20日 星期一 12时48分16秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
#if 0
	int fd = -1;
	
	fd = open("somefile", O_RDONLY);
	if (fd < 0) {
		perror("open somefile");
		exit(1);
	}

#endif

#if 0
	int fd = -1;
	fd = open("./somefile", O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open somefile");
		exit(1);
	}
#endif
	int fd = -1;
	fd = open("./", O_WRONLY);
	if (fd < 0) {
		perror("open somedir");
		exit(1);
	}

	return 0;
}
