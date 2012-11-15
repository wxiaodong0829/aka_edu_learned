/*************************************************************************
    > File Name: printf.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月03日 星期五 16时24分00秒
 ************************************************************************/

#include <stdio.h>
#define MAX_INT_LEN 0
#if MAX_INT_LEN
int max(int len, ...)
{
	int i;
	void * p = (char *)&len + 4;
	int mx = *(int *)p;

	for (i = 0; i < len; i++, p = (char *)p + 4) {
		if (mx < *(int *)p)
			mx = *(int *)p;
	}
	return mx;
}
#endif
int max(int len, ...)
{
	int i;
	void * p = (char *)&len + 4;
	int mx = *(int *)p;

	for (i = 0; i < len; i++, p = (char *)p + 4) {
		if (mx < *(int *)p)
			mx = *(int *)p;
	}
	return mx;
}
int main(void)
{
	int m = 0;
	m = max(3, 1, 3, 5);
	printf("max = %d\n", m);
	
	return 0;
}

