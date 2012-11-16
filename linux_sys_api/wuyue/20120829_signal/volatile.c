/*************************************************************************
    > File Name: volatile.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 14时18分43秒
 ************************************************************************/

/*                           */

#include <stdio.h>
#include <string.h>
#include <signal.h>

#if VOLATILE
volatile int a = 0;
#else
int a = 0;
#endif

void sig_int(int signo)
{
	a = 1;
}
/*
 *gcc -g volatile.c -o app 
 *gcc -g volatile.c -o app  -O2 
 *
 * */
int main(void)
{
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = sig_int;
	sigaction(SIGINT, &act, NULL);

	while(!a);

	return 0;
}
