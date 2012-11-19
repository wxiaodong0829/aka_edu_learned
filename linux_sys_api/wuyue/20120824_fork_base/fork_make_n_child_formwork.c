/*************************************************************************
    > File Name: fork_make_n_child_formwork.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 14时53分11秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#define NUM 5

int main(int argc, char *argv[])
{
	int n = NUM;
	int i;
	pid_t pid;

	if (argc == 2)
		n = atoi(argv[1]);

	for (i = 0; i < n; i++) /* 此模型中 两点优点：1,可创建 n 个子进程 2, i 从0 到n-1,依次是创建的子进程编号，i == n 表示父进程*/
		if ((pid = fork()) == 0)
			break;

	if (i == n) { /* parent */
		sleep(n);
		printf("I'm parent\n");
	} else { /* child */
		sleep(i);
		printf("I'm %dth child\n", i + 1);
	}


	return 0;
}	
