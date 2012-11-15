/*************************************************************************
    > File Name: scanf.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 16时50分07秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, const char *argv[])
{
	int i, j, k;
	char str[100];

	//input a integer
	printf("Please input a integer:");	
	scanf("%d", &i);
	printf("%d\n", i);

	//input some integers
	printf("Please input 3 integers:");
	scanf("%d %d %d", &i, &j, &k);
	printf("i = %d, j = %d, k = %d \n", i, j, k);

	//input a string
	printf("Please input a string:");
	scanf("%s", str);
	printf("%s\n", str);

	return 0;
}
