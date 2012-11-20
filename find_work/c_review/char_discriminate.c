/*************************************************************************
    > File Name: char_discriminate.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年11月19日 星期一 19时40分34秒
 ************************************************************************/

#include <stdio.h>

char *s = "sssssssss";
char buf[] = {'b','b','b','b','b','b','b','b'};

int main(void)
{
	char *sl = "slslslslslslslslsl";
	char bufl[] = {'l', 'l', 'l', 'l', 'l', 'l', 'l', 'l'};

	printf(".txt main = %p\n", main);
	printf(".rodata s = %p, &(s + 1) = %p, s+1 = %c\n", s, s + 1, *(s + 1));
	printf(".data buf = %p, &buf[1] = %p, buf[1] = %c\n", buf, &buf[1], buf[1]);

	printf(".stack sl = %p, &(sl + 1) = %p, sl+1 = %c\n", sl, sl + 1, *(sl + 1));
	printf(".stack bufl = %p, &bufl[1] = %p, bufl[1] = %c\n", bufl, &bufl[1], bufl[1]);




	return 0;
}
