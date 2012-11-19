/*************************************************************************
    > File Name: mysleep_suspend.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 19时00分46秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <string.h>

void sig_int(int signo)
{
}
int mysleep(int nsec)
{
	struct sigaction act, oldact;
	sigset_t new, old, sus_set;
	int unslept;

	memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = sig_int;
	sigaction(SIGALRM, &act, &oldact);              /* A */

	sigemptyset(&new);
	sigaddset(&new, SIGALRM);
	sigprocmask(SIG_BLOCK, &new, &old);				/* B */

	alarm(nsec);

	sus_set = old;
	sigdelset(&sus_set, SIGALRM);
	sigsuspend(&sus_set);

	unslept = alarm(0);

	sigaction(SIGALRM, &oldact, NULL);			/* A' */
	
	sigprocmask(SIG_UNBLOCK, &old, NULL);			/* B' */
	
	return unslept;
}

int main(void)
{
	while(1) {
		mysleep(2);
		printf("Two seconds passed\n");
	}



	return 0;
}
