/*************************************************************************
    > File Name: print.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 16时28分47秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
	int i = 10;
	float num = 3.14;

	//print string
	printf("Hello world!\n");

	//print a integer
	printf("i = %d\n", i);

	//print a hexadecimal number
	printf("i = 0x%x\n", i);

	//floating point numbers
	printf("num = %f\n", num);

	return 0;
}
