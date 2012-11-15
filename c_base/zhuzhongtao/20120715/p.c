/*************************************************************************
    > File Name: p.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月15日 星期日 15时35分45秒
 ************************************************************************/

#include<stdio.h>

int power(int x, int n)
{
	if(n==0) return 1;
	if(n%2) return power(x*x, (n-1)/2) * x;
	else	return power(x*x,     n/2);
}
int main(void)
{
	printf("%d\n", power(2, 10));
	return 0;
}
