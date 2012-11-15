/*************************************************************************
    > File Name: max_3.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 17时43分18秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, const char *argv[])
{

	int max, a, b, c;

	printf("Please input 3 num");
	scanf("%d %d %d", &a, &b, &c);

	max = a;

	if(max < b)
		max = b;
	if(max  < c)
		max = c;
	
	printf("max of 3 num is : %d\n", max);

	return 0;
}
