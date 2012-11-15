/*************************************************************************
    > File Name: strrindex_dong.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月19日 星期四 16时13分28秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int strrindex(char s[], char t[])
{
	int i, j, k;
	int lens = strlen(s);
	int lent = strlen(t);
	int retu = -1;

	//for(i = lens-1; i >= 0; i--){
	for(i = lens-1; i >= lent - 1; i--){
		for(j = i, k = lent-1; k >= 0 && s[j] == t[k]; j--, k--)
			;
		if(k == -1)
		retu = j + 1;	
	}

	return retu;
}

int main(void)
{
	char s[] = "The life that I have is all that I have";
	char t[] = "have";

	printf("%d\n", strrindex(s, t));

	return 0;
}
