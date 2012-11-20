/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月04日 14时26分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

void init(int (*arr)[5])
{
	int i, j;
	srand(time(NULL));
	for(i=0; i<5; i++)
		for(j=0; j<5; j++)
			arr[i][j]=rand()%100;
}
void show(int (*arr)[5])
{
	int i, j;
	for(i=0; i<5; i++){
		for(j=0; j<5; j++)
			printf("%4d",arr[i][j]);
		printf("\n");}
}
void sel(int p[], int n)
{
	int i,j;
	int tmp = 0;
	for (j=0; j<n; j++){
		for (i=j; i<n; i++)
			if(p[j] > p[i])
			{
				tmp = p[j];
				p[j] = p[i];
				p[i] = tmp;
			}
	}
}
int main()
{
	int arr[5][5];
	int i;
	init(arr);
	for (i=0; i<5; i++)
		sel(arr[i], 5);
	show(arr);
	printf("---------------------------------\n");
	sel(arr[0], 25);
	show(arr);
	return 0;
}
