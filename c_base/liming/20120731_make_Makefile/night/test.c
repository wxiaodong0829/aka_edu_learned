/*************************************************************************
    > File Name: test.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月31日 星期二 18时53分37秒
 ************************************************************************/

#include <stdio.h>

#define PRINT_INT(n) printf(#n" = %d\n", n)
#define PRINT_POI(n) printf(#n" = %p\n", n)
#define PRINT_CHAR(n) printf(#n" = %c\n", n)
#define PRINT_CHARAR(n) printf(#n" = %s\n", n)


int main(void)
{
	char a[][5] = {"abc","de"};
	char *p = a;
//	p1 = &a[0];
	PRINT_POI(a);
	PRINT_POI(p);
	PRINT_POI(&a[0]);
	PRINT_POI(&a[0][0]);
	PRINT_CHARAR(a[0]);
	PRINT_CHARAR(a+1);

	return 0;
}
