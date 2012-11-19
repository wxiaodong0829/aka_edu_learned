/*************************************************************************
    > File Name: timer_creat_clock.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月01日 星期六 15时16分21秒
 ************************************************************************/
/*   gcc -lrt  */

#include <stdio.h>
#include <time.h>
#include <signal.h>

void my_handler(int signo, siginfo_t *info, void *context)
{
	char *p;
	p = (char *)info->si_value.sival_ptr;
	printf("%s\n", p);
}
void tfn(union sigval arg)
{
	char *p;
	p = (char *)arg.sival_ptr;
	printf("%s", p);
}
#if DEBUGTHREAD 
int main(void)
{
	struct sigaction act;
	timer_t timer_id;
	struct sigevent evp;
	char buf[BUFSIZ] = "hello world\n";
	struct itimerspec it = {{1, 0}, {1, 0}};

//	memset(&act, 0, sizeof(act));
//	act.sa_handler = tfn;

//#if 1
	evp.sigev_notify = SIGEV_THREAD;
	evp.sigev_notify_function = tfn;
	evp.sigev_notify_attributes = NULL;
	evp.sigev_value.sival_ptr = buf;

	timer_create(CLOCK_REALTIME, &evp, &timer_id);
	timer_settime(timer_id, TIMER_ABSTIME, &it, NULL);
	
	while(1);

	return 0;
}
#endif
