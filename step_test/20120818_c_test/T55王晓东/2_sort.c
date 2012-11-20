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

int num_bit(unsigned int a)
{
	int i;
	int num;
	for (i = 0, num = 0; i < sizeof(unsigned int); i++) {
		if ((a & 1) == 1)	
			num++;
		a = a>>1;
	}
	return num;
}
int cmp(const void *a, const void *b)
{
	return	num_bit(*(unsigned int *)a) >  num_bit(*(unsigned int *)b) || *(unsigned int *)a > *(unsigned int *)b;
}

void sort(unsigned int *a, int len)
{
	qsort(a, len, sizeof(unsigned int), cmp);
}

int main(void)
{
	int i;
	unsigned int a[] = {1, 2, 5, 4, 3, 7};

	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++)
		printf("a[%d] : %d  %d\n", i, a[i], num_bit(a[i]));
	printf("\n\n");
	
	sort(a, sizeof(a)/sizeof(a[0]));

	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++)
		printf("a[%d] : %d  %d\n", i, a[i], num_bit(a[i]));

	return 0;
}
