/*************************************************************************
    > File Name: print_SFR.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年10月16日 星期二 11时30分31秒
 ************************************************************************/

#include "stdio.h"

void print_SFR(const volatile unsigned int start, const volatile unsigned int end)
{
	volatile unsigned int i = start;
	for (; i <= end; i += 4) {
		my_printf("*(volatile unsigned int %x) = %x\r", i, *(volatile unsigned int *)i);
	}
}
