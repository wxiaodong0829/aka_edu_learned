/*************************************************************************
    > File Name: mmap_fgets_new.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月21日 星期二 18时51分25秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "err.h"

// \n or size-1 个字符时结束.
char *map_fgets(char *buf, int size, int fd)
{
	char *p_map;
	int off = lseek(fd, 0, SEEK_CUR);
	int map_start = (off / 4096) * 4096;
	int distanc = off - map_start;
	int len = lseek(fd, 0, SEEK_END);
	int i, j;

	if (len == off)
		return NULL;

	p_map = mmap(NULL, BUFSIZ, PROT_READ, MAP_PRIVATE, fd, map_start); //立即 写出  munmap(p_map, BUFSIZ);
	if (p_map == MAP_FAILED)
		error_sys("mmap error :");

	for (i = distanc, j = 0; j < size - 1; i++, j++) {
		buf[j] = p_map[i];
		if (p_map[i] == '\n') {
			j++;
			break;
		}
	}
	buf[j] = '\0';

	lseek(fd, off + j, SEEK_SET);
	munmap(p_map, BUFSIZ);
	return buf;
}
int main(void)
{
	int fd;
	char buf[BUFSIZ];
	char *d;
	int i = 0;

	if ((fd = open("hello", O_RDONLY)) == -1)
		error_sys("open error: ");
	while ((d = map_fgets(buf, BUFSIZ, fd)) != NULL) {
		//fputs(buf, stdin);
		printf("buf[%d]: %s", i, d);
		i++;
	}
	close(fd);
	
	return 0;
}
