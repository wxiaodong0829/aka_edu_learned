/*************************************************************************
    > File Name: sign.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月23日 星期一 13时45分58秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 512

char line1[MAXLINE];
char line2[MAXLINE];

int Getline(char *s) 
{
	int c, i;
	i = 0;
	while ((c=getchar()) != EOF  && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return s[0];
}
void swap(char a[], int i, int j)
{
	     char tmp = a[i]; a[i] = a[j]; a[j] = tmp;
}
int partition(char *a, int l, int r)
{
	int i, j;
	for (j=l, i=l+1; i<=r; i++)
				if ((a[i] = tolower(a[i])) < (a[l] = tolower(a[l]))) swap(a, i, ++j);
	swap(a, l, j);
	return j;
}
void sort(char *a, int l, int r)
{
	if (l>=r) return;
	int k = partition(a, l, r);
	sort(a, l, k-1);
	sort(a, k+1, r);
}
void show(char *line1, char *line2)
{
	printf("%s %s\n", line1, line2);	


}
int main(void)
{
	int len=0;
	while (scanf("%s", line1) != EOF) {
		strcpy(line2, line1);
		sort(line1, 0, strlen(line1)-1);
		show(line1, line2);
	}
	return 0;
}
