/*************************************************************************
    > File Name: 6_itoa.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 13时45分52秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define ITOA(n) "0123456789"[n]
#define CHAR_BUF 30
void reverse(char *buf, int l, int r)
{
	char tmp;
	while (l < r) {
		tmp = buf[l];
		buf[l] = buf[r];
		buf[r] = tmp;

		l++;
		r--;
	}
}
char *itoa(unsigned n)
{
	int sign = 0;
	int i = -1;
	char *p = NULL;
	p = malloc(CHAR_BUF);

	if ((sign = n) < 0) {
		p[0] = '-';
		sign = -1;
		i = 0;
		n = -n;
	}

	do {
		p[++i] = ITOA(n%10);
	} while (n = n/10);
	p[++i] = '\0';

	if (sign == -1) {
		reverse(p, 1, i-1);
		return p;
	} 
	reverse(p, 0, i-1);

	return p;
}
int main(void)
{
	char *p = itoa(-100);
	char *p1 = itoa(0);
	char *p2 = itoa(100);
	printf("%s\n", p);
	printf("%s\n", p1);
	printf("%s\n", p2);
	free(p);
	free(p1);
	free(p2);

	return 0;
}
