/*************************************************************************
    > File Name: A_to_a.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月14日 星期六 08时15分15秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

#define N 1024

char convert(char ch)
{
	if((ch >- 'a') && (ch <='z'))
		return ch - 32;
	else if((ch >= 'A') && (ch <= 'Z'))
		return ch + 32;
	else
		return ch;
}

int main(int argc, const char *argv[])
{
	char arr[N] = "AKAedu 123 heLLO!";
	int i, len = strlen(arr);

	printf("%s\n\n", arr);
	printf("%s\n\n", arr);
	for(i = 0; i< len; i++)
	{
		arr[i] = convert(arr[i]);
	}

	printf("After convert...\n\n");
	printf("%s\n", arr);

	return 0;
}
