/*************************************************************************
    > File Name: const.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月12日 星期日 16时24分54秒
 ************************************************************************/

#include <stdio.h>

int main(void)
{
	int n = 0;
	int *p = &n;
	const int * mp = p;

	printf("n = %d\n", n);
	printf("&n = %p\n", p);
	printf("&p = %p\n", &p);
	printf("mp = %p\n", mp);
	printf("&mp = %p\n", &mp);//const 是 放在栈中的内容。

	return 0;
}
