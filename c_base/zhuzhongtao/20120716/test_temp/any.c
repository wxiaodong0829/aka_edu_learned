/*************************************************************************
  > File Name: squeeze.c
  > Author: wxiaodong
  > Mail  : wxiaodong0829@163.com 
  > 自由  谐作   创造   沟通
  > Created Time: 2012年07月16日 星期一 16时39分01秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int any(char s1[], char s2[])
{
	int i = 0;
	int j = 0;

	int flag = 0;

	//for (i = 0; i<strlen(s2); i++)
	for (i = 0; s2[i]; i++)
	{
		for (j = 0; s1[j]; j++)
			if (s1[j] == s2[i])
			{
				flag = 1;
				printf("%d \n", j);
			}
	}
	return flag;
}

int main(void)
{
	int flag = -1;
	char s2[] = "a";//bcdefghijklmnopqrstuvwxyz";
	char s1[] = "as";//ldfkhjqwopiuthsalgajsthiuahsdfjtijaosuhfdal;sdfjoi1u9879235019j;lashdofghaosdfjasjga;sgh";

	if( !(any(s1, s2)) ) 
	{
		printf("Read me ,you programe is wrrow\n");
		return -1;
	}


	return 0;
}
