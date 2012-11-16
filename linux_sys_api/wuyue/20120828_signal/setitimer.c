/*************************************************************************
    > File Name: alarm.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月28日 星期二 10时40分36秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(void)
{
	struct itimerval it;
	int c;

	it.it_value.tv_sec = 1;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &it, NULL);
	for (c = 0; c < 300000000; c++)
		;
	printf("counter=%d ", c);
	return 0;
}
