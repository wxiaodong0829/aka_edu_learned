/*************************************************************************
    > File Name: alarm.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月28日 星期二 10时40分36秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int counter;
	alarm(1);
	for (counter = 0; 1; counter++)
		printf("counter=%d ", counter);
	return 0;
}
