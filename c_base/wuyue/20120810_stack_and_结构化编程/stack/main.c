/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月10日 星期五 10时48分54秒
 ************************************************************************/

#include <stdio.h>
#include "stack.h"

int main(void)
{
	int n;

	while(1) {
		scanf("%d", &n);
		if (n == -1)
			break;
		push(n);
	}
	while(is_empty() == 0) {
		n = pop();
		printf("%4d", n);
	}
	printf("\n");
	return 0;
}
