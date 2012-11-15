/*************************************************************************
    > File Name: insertation.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月11日 星期六 09时56分12秒
 ************************************************************************/

#include <stdio.h>

typedef int mytype;
void insertation_sort(int a[], int n)
{
	int i, j, t;

	for (i = 1; i < n; i++) {
		t = a[i];
		for (j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;

#ifdef DEBUG
		printf("%dth : ", i);
		for (j = 0; j < n; j++)
			printf("%d ", a[j]);
		printf("\n");
#endif
	}
}
#ifdef DEBUG
int main(void)
{
	int a[] = {5, 4, 2, 3, 1}, i;

	insertation_sort(a, 5);

	for (i = 0; i < 5; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
#endif
