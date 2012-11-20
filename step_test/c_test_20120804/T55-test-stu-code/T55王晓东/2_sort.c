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
#define MAXLEN 10
#define swap(x, y) {int tmp; tmp = x; x = y; y = tmp;}

void init(int *num, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		num[i] = rand()%100;
	}
}
void print(int *num, int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%d\n", num[i]);
	printf("\n\n");
}
void chose_sort(int *num,int len)
{
	int i, j, indx;
	for (i = 0; i < len; i++) {
		indx = i;
		for (j = i + 1; j < len; j++)
			if (num[indx] > num[j])
				indx = j;
		swap(num[i], num[indx])
	}
}
 
void mopo(int *num, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
		for(j = i + 1; j < len; j++)
			if (num[i] > num[j])
				swap(num[i], num[j])
}
int main(void)
{
	int num[MAXLEN];
	int len = sizeof(num)/sizeof(num[0]);
	int chose;
	
	init(num, len);
	print(num, len);
	
	scanf("%d", &chose);
	switch (chose){
		case 1: mopo(num, len); break;
		case 2: chose_sort(num, len); break;
		default:
				return -1;
	}
	printf("\n\n");
	print(num, len);


	return 0;
}
