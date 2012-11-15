/*************************************************************************
    > File Name: rightrot.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月16日 星期一 14时45分48秒
 ************************************************************************/

#include<stdio.h>

#define rightrot(type, number, n, y) { \
	typeof(type) x = number; \
	for (int i=0; i < n; i++) \
	x = ((x>>1) | ((x&1) << sizeof(type))); \
	y = x; \
} \

int main(void)
{
	int numb1 = 4; 
	char ch1  = 4; 
	long lon1 = 4; 

	typeof(numb1) numb2;
	rightrot(typeof(numb1), 4, 1, numb2);
//	typeof(ch1) ch2 = rightrot(typeof(ch1), 4, 1);
//	typeof(lon1) lon2 = rightrot(typeof(lon1), 4, 1);

	printf("%d\n", numb2);
//	printf("%c\n", ch2);
//	printf("%ld\n", lon2);

	return 0;
}
