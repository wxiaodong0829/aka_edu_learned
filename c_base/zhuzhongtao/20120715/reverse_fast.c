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

int main()
{
	int l = 0, r = 0; // l, r, 均为下标
	int i;
	char len[MAX_LEN];

	Getline(len, MAX_LEN);
	for(i = 0; len[i] != '\0'; i++)
		;

	r = (i - 1) / 2;			//根据不同的格式发生变化//现在 r 是指在\n处
	while(l < r) swap(len, l++, r--);	//先颠倒前半部分
	l = (i - 1) / 2 +1; 
	r = i - 1; 
	while(l < r) swap(len, l++, r--);
	l = 0;
	r = i - 1;
	while(l < r) swap(len, l++, r--); 


	for(i = 0; len[i] != '\0'; i++)
		printf("%c", len[i]);
	printf("\n");

}
