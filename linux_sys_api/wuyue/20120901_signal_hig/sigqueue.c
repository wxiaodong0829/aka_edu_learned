/*************************************************************************
    > File Name: sigqueue.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月01日 星期六 10时54分50秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

void my_handler(int signo, siginfo_t *info, void *context) //必须用 sigqueue 发送的信号，才能
{
	int *p;
	p = (int *)info->si_value.sival_ptr;
	printf("%d %d \n", info->si_signo, *p);
}
int main(void)
{
	struct sigaction act;
	pid_t pid;
	int *p;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = my_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);

	p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANON, -1, 0);

	pid = fork();
	if (pid == 0)
	//	pause();
		sigsuspend(&old);
	else {
		sigval_t value;
		value.sival_ptr = (void *)p;
		*p = 100;
		//sleep(1);
		sigqueue(pid, SIGINT, value);//

		wait(NULL);
		munmap(p, sizeof(int));
	}

	return 0;
}
