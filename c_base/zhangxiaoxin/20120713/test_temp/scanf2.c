/*************************************************************************
    > File Name: scanf2.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 17时52分29秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, const char *argv[])
{
	int a, b, c;


	printf("Please inout 3 num:");
	scanf("%d %d %d", &a, &b, &c);

	if((a < 0) || (b < 0) || (c <0))
	{
		printf("lnvariable input!\n");
	}
	else
	{
		if(((a + b) > c) && ((a + c) > b) && ((b + c) > c))
		{
			printf("a = %d, b = %d, c = %d can found a triangle\n", a, b, c);
		}
		else
		{
			printf("a = %d, b = %d, c = %d can not found a triangle\n", a, b,c);
		}
	}
	return 0;
}
