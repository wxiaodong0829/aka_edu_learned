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

int flag = 0;

void my_handler(int signo)
{
	flag = 1;
}
int main(void)
{
	struct sigaction act;
	struct itimerval it = {1, 0, 1, 0};
	int i;

	memset(&act, 0, sizeof(act));
	act.sa_handler = my_handler;
	sigaction(SIGALRM, &act, NULL);

	setitimer(ITIMER_REAL, &it, NULL);


	while(1) {
		for (i = 0; !flag; i++)
			;
		flag = 0;
		printf("%d\n", i);
	}

	return 0;
}
