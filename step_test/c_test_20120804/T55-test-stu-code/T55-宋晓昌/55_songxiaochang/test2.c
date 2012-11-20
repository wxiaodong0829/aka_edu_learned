#include<stdio.h>
#include<time.h>
int main(void)
{
	int min,i,k,j;
	int num[10];
	int tmp;
	srand(time(NULL));
	for(i=0;i<10;i++)
	{
		num[i]=rand()%100;
		printf("%d\t",num[i]);
	}
	printf("\n");
	for(j=0;j<10;j++)
	{
		 min=j;
		for(k=j+1;k<10;k++)
		{
			if(num[min]>num[k])
			min=k;
		}
		tmp=num[j];
		num[j]=num[min];
		num[min]=tmp;
	}
	for(i=0;i<10;i++)
	{
		printf("%d\t",num[i]);
	}
	return 0;
}
