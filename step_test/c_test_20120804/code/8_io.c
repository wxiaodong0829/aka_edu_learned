/*************************************************************************
    > File Name: 8_io.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 15时12分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMSIZE 30
#define ITOA(n) "0123456789"[n]
#define CHAR_BUF 30
void reverse(char *buf, int l, int r);
char *itoa(unsigned n);
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

void more(char *dest, char const *src)
{
	int i;
	int a;
	a = atoi(src);
	for (i = 0; a > 0; i++) {
		if (i == 2) {
			dest[i++] = '.';
		}
		if ((i - 2)%4 == 0) {
			dest[i++] = ',';
		}
		dest[i] = a%10 + '0';
		a = a/10;
	}
	dest[i++] = '$';
	dest[i] = '\0';
	reverse(dest, 0, i-1);
}
void dollars(char *dest, char const *src)
{
	int len = strlen(src);
	int i;
//	for (i = 0; i < len; i++)
//		printf("%c ", src[0]);
	if (len < 3) {
		switch (len) {
			case 1:
				dest[0] = '$';
				dest[1] = '0';
				dest[2] = '.';
				dest[3] = '0';
				dest[4] = src[0];
				dest[5] = '\0';
				break;
			case 2:
				dest[0] = '$';
				dest[1] = '0';
				dest[2] = '.';
				dest[3] = src[0];
				dest[4] = src[1];
				dest[5] = '\0';
				break;
			default:
				break;

		}
	} else more(dest, src);
	return;
}
int main(void)
{
	int in, a;
	scanf("%d", &in);
	char *src = itoa(in);
	char *dest = malloc(NUMSIZE);
	//printf("%s\n", p);
	dollars(dest, src);
	printf("%s\n", dest);
	
	free(src);
	free(dest);

	return 0;
}
