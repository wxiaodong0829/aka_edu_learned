/*************************************************************************
    > File Name: binsearch.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月17日 星期二 15时11分20秒
 ************************************************************************/

#include<stdio.h>
#define N 100
int a[] =  {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
		47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
void primes(int n)
{
	int i, j, k;
	printf("2, ");
	for (i=3, k=0; i<=n; i+=2) {
		for (j=2; j*j < i; j++)
			if (i%j == 0) break;
		if (j*j > i) printf("%d\n", i);
//		if (j*j > i) {
//			a[k++] = i;
//			printf("%3d", i);
//		}
	}
	a[k] = '\0';
}
int bsearch(int key, int l, int r)
{
	int m;
	while (l <= r) {
		m = (l+r)/2;
		if		(key < a[m]) r = m - 1;
		else if (key > a[m]) l = m + 1;
		else return m;
	}
	return -1;
}
int search(int key, int l, int r)
{
	int m;
	while (l <= r) {
		m = (l+r)/2;
		if (key<a[m]) r = m - 1;
		else          l = m + 1;
	}
	if (key == a[r]) return r;
	else			 return -1;
}
int main(void)
{
//	primes(100);
	
	//printf("\n%d\n", bsearch(53, 0, sizeof(a)/sizeof((int) - 1)));
	printf("\n%d\n", search(53, 0, sizeof(a)/sizeof((int) - 1)));

	return 0;
}
