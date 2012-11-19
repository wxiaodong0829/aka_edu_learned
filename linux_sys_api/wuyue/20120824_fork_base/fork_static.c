/*************************************************************************
    > File Name: fork_static.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 15时30分30秒
 ************************************************************************/


/************
 * 验证　父子　不共享 数据段.data 中的　全局变量　
 *
 *
 * ********/

#include <stdio.h>
#include <unistd.h>

int n = 1;

int main(void)
{
	pid_t pid;
	int i;

	for (i = 0; i < 1; i++)
		if ((pid = fork()) == 0) {
			break;
		}


	if (i == 1) {
		sleep(1);
		printf("I'm parent n = %d\n", n);
	} else {
		n++;
		printf("I'm %dth child n = %d \n", i + 1, n);
	}


	return 0;
}
