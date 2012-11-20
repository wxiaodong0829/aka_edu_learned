/*************************************************************************
    > File Name: atox.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年10月16日 星期二 19时53分35秒
 ************************************************************************/

#include <stdio.h>
#include "lib.h"

int main(void)
{
	char *s = "0x12345678";
	int n = atox(s);
	printf("n = %x\n", n);
	return 0;
}
