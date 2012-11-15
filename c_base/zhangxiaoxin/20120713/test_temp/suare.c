/*************************************************************************
  > File Name: suare.c
  > Author: wxiaodong
  > Mail  : wxiaodong0829@163.com 
  > 自由  谐作   创造   沟通
  > Created Time: 2012年07月14日 星期六 09时07分29秒
 ************************************************************************/

#include<stdio.h>

int main(int argc, const char *argv[])
{
	int i, n;

	printf("this program print a table of square\n");
	printf("Enter numver of entries in table:");
	scanf("%d", &n);

	for(i = 1; i<= n; i++)
	{
		printf("%10d%10d\n", i, i*i);
	}
	return 0;
}
