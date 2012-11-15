/*************************************************************************
    > File Name: lingxing.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月14日 星期六 09时17分29秒
 ************************************************************************/

#include<stdio.h>

int main(int argc, const char *argv[])
{
	int i, j, k;
	int n;

	while(scanf("%d", &n))
	{
		if(n & 1)
			break;
		k = n / 2;

		for(i = -k; i<= k; i++)
		{
			if(i < 0)
			{
				for(j = 0; j< i+k+1; j++)
					printf("*");
			}
			else
			{
				for(j = 0; j < -i+k+1; j++)
					printf("*");
			}
			printf("\n");
		}
	}

	return 0;
}
