/*************************************************************************
    > File Name: recursion.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月15日 星期日 19时05分47秒
 ************************************************************************/

#include<stdio.h>

int recursion(int x, int n)
{
	if (1 == n) return x;
	else if (n%2 == 1) return recursion(x*x, n/2) * x; 
	else			   return recursion(x*x, n/2); 
}

int main()
{
	int n = recursion(2, 10);
	printf("%d", n);
	return 0;
}
