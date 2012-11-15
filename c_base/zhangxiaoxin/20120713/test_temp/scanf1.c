/*************************************************************************
    > File Name: scanf1.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 16时52分50秒
 ************************************************************************/

#include<stdio.h>

#define N 1024

int main(int argc, const char *argv[])
{
	char str[N];

	printf("Please enter <hello world>:");
	scanf("%s",str);
	printf("%s\n", str);

	return 0;
}


