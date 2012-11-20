/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月04日 12时52分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <time.h>

void init(int *p)
{
	int i;
	srand(time(NULL));
	for (i=0; i<10; i++)
		*(p+i) = rand()%100;
}
void popo(int *p)
{
	int i, j;
	int tmp = 0;
	for (i=0; i<10; i++)
		for(j=10; j>i; j--)
			if(p[i] > p[j])
			{
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
	for (i=0; i<10; i++)
		printf("%d\n", *(p+i));
}

void sel(int *p)
{
	int i,j,k;
	int tmp = 0;
	for (j=0; j<10; j++){
		for (i=j; i<10; i++)
		if(p[j] > p[i])
		{
		tmp = p[j];
		p[j] = p[i];
		p[i] = tmp;
		}
	}
	for (i=0; i<10; i++)
		printf("%d\n", *(p+i));
}
int main()
{
	int num[10];
	init(num);
//	popo(num);
	sel(num);
	//printf("%d\n", num[5]);
	return 0;
}
