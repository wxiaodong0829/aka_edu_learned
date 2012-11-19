/*************************************************************************
    > File Name: dup2.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月23日 星期四 11时41分16秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "err.h"

/*   ./app [outfilename] */
int main(int argc, char **argv)
{
	int fd;

	if (argc == 2) {
		if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) 
			error_sys("open ");
		dup2(fd, STDOUT_FILENO);
	}

	printf("Hello word!");

	return 0;
}

