/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月31日 星期二 09时20分46秒
 ************************************************************************/

//#include <stdio.h>
extern int printf(__const char *fmt, ...);
#include "add_sub.h"

int main(void)
{
	int a = 100;
	int b = 200;

	PRINT(PI);

	printf("a + b = %d\n", add(a, b));
	printf("a - b = %d\n", sub(a, b));
	return 0;
}
