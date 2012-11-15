/*************************************************************************
    > File Name: static.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月29日 星期日 15时40分21秒
 ************************************************************************/

#include <stdio.h>
void func(void)
{
	static int n  = 0x12345678;
	printf("%x\n", n);
	n++;
}
int main(void)
{
	while (1) {
		func();
		sleep(1);
	}
	return 0;
}
