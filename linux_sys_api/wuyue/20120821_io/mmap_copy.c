/*************************************************************************
    > File Name: mmap_copy.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月21日 星期二 14时12分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "err.h"
int main(int argc, char *argv[])
{
	int fd_src, fd_dest;
	long long len;
	long long i;
	char *p_src, *p_dest;
	char c = '\0';
 
	if (argc !=3)
		error_user("usage: ./mycp src dest");

	if ((fd_src = open(argv[1], O_RDONLY )) == -1)
		error_sys("open src: ");
	// 建立可写映射区，必须以读写方式打开
	if ((fd_dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC , 0644)) == -1)
		error_sys("open dest: ");

	len = lseek(fd_src, 0, SEEK_END);

	lseek(fd_dest, len - 1, SEEK_SET); //拓展文件，并在等待最后一个字节等待被覆盖
	write(fd_dest, &c, 1);                 

	p_src = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd_src, 0);

	p_dest = mmap(NULL, len, PROT_WRITE, MAP_SHARED, fd_dest, 0);

	if ((p_src == MAP_FAILED) || (p_dest == MAP_FAILED))
		error_sys("mmap src or dest filed");

	close(fd_src);
	close(fd_dest);

	for (i = 0; i < len; i++)
		p_dest[i] = p_src[i];

	munmap(p_src, len);
	munmap(p_dest, len);
	return 0;
}
