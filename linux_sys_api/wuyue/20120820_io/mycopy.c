/*************************************************************************
    > File Name: mycopy.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月20日 星期一 15时06分19秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define NEW_PERM 0644

void error_sys(char *err)
{
	perror(err);
	exit(1);
}
void error_user(char *err)
{
	perror(err);
	exit(2);
}
/* ./mycopy src dest */
int main(int argc, char *argv[])
{
	int ret_read;
	int fd_src;
	int fd_dest;
	char buf[BUFSIZ];

	if (argc != 3)
		error_user("page: ./a.out src dest");

	if ((fd_src = open(argv[1], O_RDONLY)) < 0) 
		error_sys("open error: ");
	if ((fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, NEW_PERM)) < 0)
		error_sys("open error: ");
	/*紧接着要写 close()*/
	
	while(ret_read = read(fd_src, buf, BUFSIZ))
		write(fd_dest, buf, ret_read);

	close(fd_src); 
	close(fd_dest);
	return 0;

}
