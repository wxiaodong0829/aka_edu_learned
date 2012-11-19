/*************************************************************************
    > File Name: sigaction.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月28日 星期二 14时41分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

void my_handler(int signo)
{
	printf("get alarm...\n");
}
int main(void)
{
	struct sigaction act;
	struct itimerval it = {1, 0, 1, 0};

	memset(&act, 0, sizeof(act));
	act.sa_handler = my_handler;
	sigaction(SIGALRM, &act, NULL);

	setitimer(ITIMER_REAL, &it, NULL);

	while(1);

	return 0;
}
