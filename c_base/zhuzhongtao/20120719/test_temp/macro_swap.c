/*************************************************************************
    > File Name: macro_swap.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月19日 星期四 14时54分28秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>

#define swap(type, x, y) {\
	type tmp;\
	tmp = x;\
	x = y;\
	y = tmp;\
}

int main(void)
{
	int i = 3, j = 5;
	double x = 3.1415926, y = 2.718281828;

	printf("%d %d\n", i, j);
	printf("%.9f %.9f\n", x, y);
	printf("%f %f\n", x, y);

	swap(int, i, j);
	printf("%d %d\n", i, j);

	swap(double, x, y);
	printf("%.9f, %.9f\n", x, y);

	return 0;
}

