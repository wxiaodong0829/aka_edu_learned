/*************************************************************************
    > File Name: fork1.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 11时38分30秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	pid_t pid;

	pid = fork();

	//write(1, " all ", 5);
	printf(" all ");

	if (pid == 0) {
		printf("I am child.");
	} else 
		printf("I am parent.");

	return 0;
}
