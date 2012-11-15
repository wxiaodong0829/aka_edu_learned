/*************************************************************************
    > File Name: poit_test.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月01日 星期三 17时57分07秒
 ************************************************************************/

#include <stdio.h>

#define PRINT_P(n)	printf(#n" = %p\n", n)
#define PRINT_INT(n)	printf(#n" = %d\n", n)
#define PRINT_CHAR(n)	printf(#n" = %c\n", n)
#define PRINT_CHARAR(n)	printf(#n" = %s\n", n)
int main(void)
{
	char (*p)[10];
	char a[10] = "aaaaa";
	p = &a;
	char *p1;
	p1 = malloc(sizeof *p1);

	PRINT_P(p1);

	PRINT_P(p);
	PRINT_P(&p);
	PRINT_P(a);
	PRINT_P(&a);
	PRINT_P(&a[9]);

	return 0;
}

