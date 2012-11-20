/*************************************************************************
    > File Name: 5_memmove.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月18日 星期六 15时55分53秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
void *memmove(void *dest, const void *src, size_t n)
{
	int i;
	char *d = dest;
	const char *s = src;
	for (i = 0; i < n; i++)
		*d++ = *s++;
	return dest;
}

int main(void)
{
	char *src = "abcdefg";

	char dest[BUFSIZ];
	char *d = dest;

	d = memmove(dest, src, strlen(src) + 1);

	puts(d);

	return 0;
}
