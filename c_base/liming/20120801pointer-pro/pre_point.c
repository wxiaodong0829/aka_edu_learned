/*************************************************************************
    > File Name: pre_point.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月01日 星期三 09时10分34秒
 ************************************************************************/

#include <stdio.h>

int main(void)
{
	char *p;
	p = 5678;

	printf("%d\n", (int)p);

	p = malloc(sizeof *p);

	printf("%p\n", p);

	return 0;
}
