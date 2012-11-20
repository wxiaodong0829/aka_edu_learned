/*************************************************************************
    > File Name: recursion.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年11月19日 星期一 20时10分48秒
 ************************************************************************/

#include <stdio.h>

int foo(int n)
{
	int ret = 0;
	if (n >= -2)
		ret = foo(n - 1) + n;
	printf("n = %d, ret = %d\n", n, ret);
	return ret;
}
int main(void)
{
	printf("%d\n", foo(5));

	return 0;
}
