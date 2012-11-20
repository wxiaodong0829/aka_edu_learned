/*************************************************************************
    > File Name: 2_sort.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 10时20分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXLEN 5 
#define swap(x, y) {int tmp; tmp = x; x = y; y = tmp;}

void init(int (*num)[5], int h)
{
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < h; j++)
			num[i][j] = rand()%100;
	}
}
void print(int (*num)[5], int h)
{
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < h; j++)
			printf("%3d", num[i][j]);
		printf("\n");
	}
}
void chose_sort2(int (*num)[5],int h)
{
	int *p = num[0];
	printf("p = %p", p);
	int len = h*h;
	int i, j, indx;
	for (i = 0; i < len; i++) {
		indx = i;
		for (j = i + 1; j < len; j++)
			if (p[indx] > p[j])
				indx = j;
		swap(p[i], p[indx])
	}
#if 0
	int i, j, indx;
	int len = h*h;
	for (i = 0; i < len; i++) {
		indx = i;
		for (j = i + 1; j < len; j++)
			if ((*((*(num+0))+indx)) > num[j])
				indx = j;
		swap(num[0][i], num[0][indx])
	}
#endif
}
void chose_sort1(int (*num)[5], int h)
{
	int k, i, j, indx;
	for (k = 0; k < h; k++) {
		for (i = 0; i < h; i++) {
			indx = i;
			for (j = i + 1; j <= h; j++)
				if (num[k][indx] > num[k][j])
					indx = j;
			swap(num[k][i], num[k][indx])
		}
	}
}

int main(void)
{
	int num[MAXLEN][MAXLEN];
	int len = sizeof(num)/sizeof(num[0][0]);
	int chose;
	printf("%p\n\n", num);
	init(num, 5);
	print(num, 5);
#if 1	
	scanf("%d", &chose);
	switch (chose){
		case 1: chose_sort1(num, 5); break;
		case 2: chose_sort2(num, 5); break;
		default:
				return -1;
	}
	printf("\n\n");
	print(num, 5);
#endif

	return 0;
}
