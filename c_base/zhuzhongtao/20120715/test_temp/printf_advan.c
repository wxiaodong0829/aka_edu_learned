/*************************************************************************
    > File Name: printf_advan.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 16时38分28秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
	
	printf("%d, 0x%x, %f\n", 100, 100, (double)100);
	printf("%%,',\'\n");
	printf("sizeof(char)= %d\n", sizeof(char));
	printf("sizeof(int) = %d\n", sizeof(int));

	return 0;
}
