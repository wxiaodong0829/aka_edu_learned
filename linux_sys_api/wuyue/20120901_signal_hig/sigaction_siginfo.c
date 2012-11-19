/*************************************************************************
    > File Name: sigaction_siginfo.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月01日 星期六 09时40分12秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

void sig_int(int signo, siginfo_t * info, void *arg)
{
	printf("I'm sig_int%d\n", signo);
}
int main(void)
{
	struct sigaction act;

	act.sa_sigaction = sig_int;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);

	while (1) 
		pause();

	return 0;
}
