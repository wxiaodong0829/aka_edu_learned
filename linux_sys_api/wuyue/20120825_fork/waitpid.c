/*************************************************************************
    > File Name: waitpid.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月25日 星期六 14时14分02秒
 ************************************************************************/

#include <stdio.h>
#include <sys/wait.h>
#include "err.h"

int main(void)
{
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		perror("fork failed");
		exit(1);
	} 
	if (pid == 0) {
		int i = 3;
		while(i-- > 0) {
			printf("This is the child\n");
			sleep(1);
		}
		exit(3);
	} else {
		int stat_val;
		waitpid(pid, &stat_val, 0);
		if (WIFEXITED(stat_val))
			printf("child exited with code %d\n", 
					WEXITSTATUS(stat_val));
		else if (WIFSIGNALED(stat_val))
			printf("child terminated abnormally, signal %d\n",
					WTERMSIG(stat_val));
	}

	return 0;
}
