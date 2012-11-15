/*************************************************************************
    > File Name: memset.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月25日 星期三 10时28分36秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(void)
{
	int src[] = {1, 2, 3, 4, 5};
	int i;
	for (i = 0; i < sizeof(src)/sizeof(src[0]); i++)
		printf("%d", src[i]);
	printf("\n");

	memset(src, ~0, sizeof(src));
	memset(src, -1, sizeof(src));
	memset(src, 0xffffffff, sizeof(src));
	memset(src, 0xff, sizeof(src));

	for (i = 0; i < sizeof(src)/sizeof(src[0]); i++)
		printf("%d", src[i]);
	printf("\n");

	return 0;
}

