/*************************************************************************
    > File Name: environ.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 10时42分24秒
 ************************************************************************/

#include <stdio.h>

int main(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] ; i++)
		printf("[%d]: %s \n", i, environ[i]);

	return 0;
}
