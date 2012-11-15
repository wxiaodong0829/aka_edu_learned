/*************************************************************************
    > File Name: reverse.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月15日 星期日 14时16分07秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 200
/* Getline : read a line into s, return length  */
int Getline(char s[], int lim)
{
	int c, i;

	for(i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

int reverse(char from[], char to[])
{
	int i = 0;
	int n = strlen(from);

	while((to[i] = from[n-i]) != '\0')
		++i;

}

int main(int argc, char *argv[])
{
	//int line=0,hang=0;
	int i = 0;
	int len = 0;
	int line[MAX_LINE];
	//int strock[MAX_LINE][MAX_LINE];	
	int strock[MAX_LINE];

	while ((len = Getline(line, MAX_LINE)) > 0){
		reverse(line, strock);

	}

	for(i=0; strock[i]!='\0'; i++){
		printf("%c",strock[i]);
	}
}
