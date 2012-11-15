/*************************************************************************
    > File Name: max3.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月30日 星期一 11时15分53秒
 ************************************************************************/

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
//#define MAX3(a, b, c)    MAX(MAX(a, b), c)
//#define MAX3(a, b, c)  (MAX(a, b) >  (c) ? MAX(a,b) : (c))
#define MAX3(a, b, c)  ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))

int main(void)
{
	printf("%d\n", MAX3(1, 2, 3));

	return 0;
}
