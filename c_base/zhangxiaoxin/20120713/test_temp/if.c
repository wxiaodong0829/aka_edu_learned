/*************************************************************************
    > File Name: if.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 17时30分12秒
 ************************************************************************/

#include<stdio.h>


int main(int argc, const char *argv[])
{
	int x;
	printf("enter a number:");
	scanf("%d", &x);
	//if
	if(x != 0)
	{
		printf("x is nonzero.\n");
	}

	//judge a num is even or odd
	if(x % 2 == 0)
	{
		printf("x is even.\n");
	}
	else{
		printf("x is odd.\n");
	}

	return 0;
}
