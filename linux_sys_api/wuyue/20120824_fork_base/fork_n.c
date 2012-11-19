/*************************************************************************
    > File Name: fork_n.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 14时10分35秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	pid_t pid;
	int i;

	int n_fork = atoi(argv[1]);

	for (i = 0; i < n_fork; i++) {
		pid = fork();
		if (pid == 0) {
			sleep(i);
			printf("child: %d\n", getpid());
			break;
		} else {
			sleep(i);
			printf("parent: %d\n",getpid());
		}
	}



	return 0;
}
