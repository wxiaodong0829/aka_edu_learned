/*************************************************************************
    > File Name: max.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月14日 星期六 08时59分38秒
 ************************************************************************/

#include<stdio.h>

#define N 10

int main(int argc, const char *argv[])
{
	int num[N] = {
		12,6,34,65,67,87,89,100,1,66
	};
	int i, max = 0;

	for(i = 0; i< 10; i++)
	{
		if(max < num[i])
		{
			max = num[i];
		}
	}

	printf("max is %d\n", max);

	return 0;
}
