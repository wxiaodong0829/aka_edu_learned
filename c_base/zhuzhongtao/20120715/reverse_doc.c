/*************************************************************************
    > File Name: reverse1.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月15日 星期日 15时12分39秒
 ************************************************************************/

#include<stdio.h>

#define MAX_LEN 100

void swap(char s[], int l, int r)
{
	int i;
	char temp;
	temp = s[l];
	s[l] = s[r];
	s[r] = temp;

}

/* Getline: read a line into s, return lenth  */
int Getline(char s[], int lim)
{
	int c, i;

	for(i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
void reverse_line(char s[], int n)
{
	int i;
	int l = 0, r = 0; 

	r = n - 1;			//根据不同的格式发生变化
	while(l < r) swap(s, l++, r--);

	for(i = 0; s[i] != '\0'; i++)
		printf("%c", s[i]);
//	printf("\n");
	
}
int main()
{
	int i;
	char len[MAX_LEN];

	Getline(len, MAX_LEN);
	for(i = 0; len[i] != '\0'; i++)
		;
	reverse_line(len, i);
	
}
