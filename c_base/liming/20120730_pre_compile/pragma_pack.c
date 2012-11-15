/*************************************************************************
    > File Name: pragma_pack.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月30日 星期一 17时19分22秒
 ************************************************************************/

#include <stdio.h>

struct test {
	char a;
	int  b;
}t;

#pragma pack()

int main(void)
{
	printf("sizeof t = %d\n", sizeof(struct test));

	return 0;
}
