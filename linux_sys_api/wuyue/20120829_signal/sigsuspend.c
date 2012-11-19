/*************************************************************************
    > File Name: sigsuspend.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 15时56分16秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <signal.h>

void sig_int(int signo)
{
	printf("I'm catch...\n");
}

int main(void)
{
	struct sigaction act;
	sigset_t new, old;

	memset(&act, 0, sizeof(act));
	act.sa_handler = sig_int;
	sigaction(SIGINT, &act, NULL);

	sigemptyset(&new);
	sigaddset(&new, SIGINT);
	sigprocmask(SIG_BLOCK, &new, &old);

	sigsuspend(&old);
	printf("I'm back ...\n");

	while(1);

	sigprocmask(SIG_BLOCK, &old, NULL);
	return 0;
}
