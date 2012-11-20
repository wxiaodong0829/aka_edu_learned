/*************************************************************************
    > File Name: 10.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 18时31分29秒
 ************************************************************************/

#include <stdio.h>
void * (*func)(void *, void *);
void *add(void *a, void *b)
{
	return (void *)(*(int *)a + *(int *)b);
}
void *sub(void *a, void *b)
{
	return (void *)(*(int *)a - *(int *)b);
}
void *mul(void *a, void *b)
{
	return (void *)(*(int *)a * (*(int *)b));
}
void *dev(void *a, void *b)
{
	return (void *)(*(int *)a / *(int *)b);
}
int main(void)
{
	char ch;
	int a, b;
	void * ret;
	ch = getchar();
	scanf("%d %d", &a, &b);
	switch (ch) {
		case '+': ret = add(&a, &b); printf("%d\n", (int)ret); break;
		case '-': ret = sub(&a, &b); printf("%d\n", (int)ret); break;
		case '*': ret = mul(&a, &b); printf("%d\n", (int)ret); break;
		case '/': ret = dev(&a, &b); printf("%d\n", (int)ret); break;
		default: break;
	}
	return 0;
}
