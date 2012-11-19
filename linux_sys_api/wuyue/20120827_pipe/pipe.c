/*************************************************************************
    > File Name: pipe.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月27日 星期一 09时46分28秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd[2]; pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid == 0) {
		char buf[32]; int n;
		close(fd[1]);
		n = read(fd[0], buf, 32);
		write(STDOUT_FILENO, buf, n);
	} else {
		close(fd[0]);
		write(fd[1], "hello", 5);
		wait(NULL);
	}

	return 0;
}
