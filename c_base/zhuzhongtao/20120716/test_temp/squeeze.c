/*************************************************************************
    > File Name: squeeze.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月16日 星期一 16时39分01秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

void squeeze(char s1[], char s2[])
{
	int i = 0;
	int j = 0;
	int k = 0;


	//for (i = 0; i<strlen(s2); i++)
	for (i = 0; s2[i]; i++)
	{
		for (j = 0, k = 0; s1[j]; j++)
			if (s1[j] != s2[i])
				s1[k++] = s1[j];
		s1[k] = '\0'; 
	}
	for(i = 0; i<strlen(s1); i++)
	{
		printf("%c",s1[i]);
	}
}

int main(void)
{
	char s2[] = "abcdefghijklmnopqrstuvwxyz";
	char s1[] = "as;ldfkhjqwopiuthsalgajsthiuahsdfjtijaosuhfdal;sdfjoi1u9879235019j;lashdofghaosdfjasjga;sgh";

	squeeze(s1, s2); 
	
	return 0;
}
