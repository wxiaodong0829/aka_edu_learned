/*************************************************************************
    > File Name: achieve_strlen.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月17日 星期二 08时49分20秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int my_strlen_fir(char s[])
{
	int i = 0;
	int len = 0;

	//end in '\0'
	while(s[i++])
		len++;
	
	return len;
}

int my_strlen_sec(char s[])
{
	int len = 0;

	for(; (*s != '\0'); s++)
		len++;

	return len;
}

int my_strlen_thi(char s[])
{
	int len = 0;
	
	for(; *s; s++)
		len++;

	return len;
}

int my_strlen_for(char s[])
{
	int len = 0;
	
	for(; *s++; )
		len++;

	return len;
}

int main(int argc, const char *argv[])
{
	char str[] = "Hello world";

	printf("strlen(str) = %d\n", strlen(str));
	printf("my_strlen_fir(str) = %d\n", my_strlen_fir(str));
	printf("my_strlen_sec(str) = %d\n", my_strlen_sec(str));
	printf("my_strlen_thi(str) = %d\n", my_strlen_thi(str));
	printf("my_strlen_for(str) = %d\n", my_strlen_for(str));

	return 0;
}
