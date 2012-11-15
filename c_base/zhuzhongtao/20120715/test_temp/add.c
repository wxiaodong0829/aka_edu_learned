/*************************************************************************
    > File Name: add.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月14日 星期六 08时12分27秒
 ************************************************************************/

#include<stdio.h>

int main(int argc, const char *argv[])
{
	int i, sum = 0;

	for(i = 1; i <= 100; i++)
	{
		sum += i;
	}

	printf("1 + 2+3+...+100 = %d\n", sum);

	return 0;
}
