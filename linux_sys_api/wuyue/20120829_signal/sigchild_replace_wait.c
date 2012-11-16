/*************************************************************************
    > File Name: sigchild_replace_wait.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 19时35分37秒
 ************************************************************************/
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "err.h"
#endif

#include "sigchild_replace_wait.h"

void sig_child(int signo)
{
	int status;
	wait(&status);
	print_exit(status);
}
int init_sig_child(int signo, int flag, struct sigaction *old)
{
	struct sigaction act;
	int ret;

	memset(&act, 0, sizeof(struct sigaction));
	//sigaddset(&act.sa_mask, signo);
	act.sa_flags = flag;
	act.sa_handler = sig_child;
	if ((ret = sigaction(signo, &act, old)) == -1)
		return -1;

	return 0;
}
int recover_sigaction(int signo, struct sigaction *old)
{
	sigaction(signo, old, NULL);
}

/* ./app [num]   */
#if DEBUG
int main(int argc, char **argv)
{
	pid_t pid;
	int i;
	int n = 5;
	struct sigaction old;

	if (argc > 1)
		n = atoi(argv[1]);

	if ((i = init_sig_child(SIGCHLD, 0, &old)) == -1)
		error_sys("sigaction");
	for (i = 0; i < n; i++) {
		if ((pid = fork()) == 0)
			break;
	}

	if (i < 0)
		error_sys("fork");
	if (i != n) {
		printf("I'm %dth child\n", i+1);
//		while(1);
		exit(i + 1);
	} else if (i == n){
		printf("I'm parent\n");
		//while(1);
	//	sleep(3);
	}
	recover_sigaction(SIGCHLD, &old);

	return 0;
}
#endif
