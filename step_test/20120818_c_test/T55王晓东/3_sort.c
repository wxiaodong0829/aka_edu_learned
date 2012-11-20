/*************************************************************************
    > File Name: 2_sort.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月18日 星期六 14时41分54秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SWAP(a, b) do {\
			unsigned int tmp;\
			tmp = a; \
			a = b;\
			b = tmp;\
		} while(0)
void sort(unsigned int *a, int len)
{
	int i, j;
	
	for (i = 0; i < len; i++) {
		if (a[i] % 2 == 1) //只插奇数
			for (j = i - 1; (j >= 0) && (a[j] % 2 == 0); j--)
				SWAP(a[j], a[j+1]);
	}
}
int main(void)
{
	int i;
	unsigned int a[] = {1, 2, 3, 4, 5, 6};

	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++)
		printf("a[%d] : %d  \n", i, a[i]);
	printf("\n\n");
	
	sort(a, sizeof(a)/sizeof(a[0]));

	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++)
		printf("a[%d] : %d \n", i, a[i]);

	return 0;
}
