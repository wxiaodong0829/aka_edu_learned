/*************************************************************************
    > File Name: itoa.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月25日 星期三 13时20分17秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXNUM 32
void swap(char *a, int l, int r)
{
	char tmp; tmp = a[l]; a[l] = a[r]; a[r]= tmp;
}
void revers(char *str, int l, int r)
{
	while (l < r) {
		swap(str, l++, r--);
	}
}
char *myitoa(unsigned n, char *str)
{
	int i = 0;
	int sign = 1;
	if ((sign = n) < 0) {
		n = -n;
		sign = -1;
	}
	do {
		str[i++] = n % 10 + '0';
	} while (n /= 10);
	if (sign == -1) {
		str[i++] = '-';
	}
	str[i] = '\0';
	revers(str, 0 , i - 1);

	return str; 
}
int main(void)
{
	int i = 123456;
	int j = -123456;
	char a[MAXNUM];
	memset(a, 0, sizeof(a));
	myitoa(i, a);
	printf("i = %d   %s\n", i, a);

	myitoa(j, a);
	printf("j = %d  %s\n", j, a);

	return 0;
}
