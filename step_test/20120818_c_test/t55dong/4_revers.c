/*************************************************************************
    > File Name: 4_revers.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月18日 星期六 15时41分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SWAP(a, b) do {\
			char tmp;\
			tmp = a; \
			a = b;\
			b = tmp;\
		} while(0)

char *revert(char *str)
{
	int l = 0, r = strlen(str) - 1;

	while (l < r) {
		SWAP(str[l], str[r]);
		l++;
		r--;
	}
	return str;
}
int main(void)
{
	char a[] = "abcdefg";
	char *ret = NULL;
	puts(a);
	ret = revert(a);
	puts(ret);

	return 0;
}
