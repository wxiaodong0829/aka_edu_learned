/*************************************************************************
    > File Name: mmap_fgets.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月21日 星期二 16时22分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "err.h"
/***********************
 * 功能：从一个已打开的映射区读取一行数据.
 * buf: 要传出的数组的首地址.
 * p_map: 已经映射在内存中的首地址.
 * point: 从 p_map 中的point 处开始复制.
 * max_len:  p_map 指向的映射区的大小.
 *
 * ********************/
char *mmap_fgets(char *buf, int size, const char * p_map, int *point, int max_len)
{
	int i, j;

	if (*point > max_len - 1)
		return NULL;

	for (i = *point, j = 0; p_map[i] != '\n' && i < size; i++, j++) {
		buf[j] = p_map[i];
	}
	buf[j] = p_map[i];
	buf[++j] = '\0';
	*point = ++i; //下一行开头

	return buf;
}
int main(int argc, char *argv[])
{
	int fd;
	int len;
	char * p_map;
	char buf[BUFSIZ];
	char *d = buf;
	int point = 0; //映射内存的下标

	//if ((fd = open("hello", O_RDONLY | O_NONBLOCK)) == -1)
	if ((fd = open("hello", O_RDONLY)) == -1)
		error_sys("open hello:");
	len = lseek(fd, 0, SEEK_END);
	p_map = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p_map == MAP_FAILED)
		error_sys("mmap error");

	while((d = mmap_fgets(d, BUFSIZ, p_map, &point, len)) != NULL) {
		printf("%d\n", point);
		puts(d);
	}
	return 0;
}
