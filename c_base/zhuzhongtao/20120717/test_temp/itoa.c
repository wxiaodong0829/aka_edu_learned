/*************************************************************************
    > File Name: itoa.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月17日 星期二 11时40分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#define N 100

void bit(int x)
{
    int i;
    printf("%+11d\t", x);
    for (i=0; i<sizeof(int)*8; i++, x=x<<1)
        printf("%d%s", !!(x&0x80000000), i%4==3?" ":"");
    printf("\n");
}

void reverse(char s[])
{
	int i, j;
	char tmp;

	for(i = 0, j = strlen(s)-1; i < j; i++, j--)
		tmp = s[i], s[i] = s[j], s[j] = tmp;
}
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		bit('0');
		s[i++] = n % 10 + '0';
		bit(n);
		bit(n%10);
		bit(n%10+'0');
	} while((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
int main(void)
{
	char a[N];
	bit(INT_MIN);
	itoa(INT_MIN, a);

	printf("%s\n", a);
	return 0;
}
