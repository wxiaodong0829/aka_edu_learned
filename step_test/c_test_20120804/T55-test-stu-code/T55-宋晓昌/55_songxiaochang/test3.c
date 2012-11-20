#include<stdio.h>
#include"sort.h"
#include<time.h>
int main(void)
{
	char num[5][5];	
	int i,j;
	srand(time(NULL));

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
		num[i][j]=rand()%100;
		printf("%d\t",num[i][j]);
		}

		printf("\n");
	}
	printf("\n");

	for(i=0;i<5;i++)
	{
		sort(num[i],5);		
		printf("\n");
	}
	printf("\n");
	return 0;
}
