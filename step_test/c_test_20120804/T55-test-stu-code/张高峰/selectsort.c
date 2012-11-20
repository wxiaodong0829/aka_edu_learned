#include<stdio.h>
#include<time.h>

#define N 10
int num[N];

void init()
{
	int i;
	srand(time(NULL));
	for(i=1;i<N;i++)
		num[i]=rand()%N;
}

void print()
{
	int i;
	for(i=0;i<N;i++)
		printf("%d ",num[i]);
	printf("\n");
}

void swap(int i,int j)
{
	int tmp;
	tmp=num[i];
	num[i]=num[j];
	num[j]=tmp;
}

void selectsort()
{
	int i,j;
	for(j=1;j<N;j++)	
		for(i=j;i>0;i--)
			if(num[i]<num[i-1])
				swap(i,i-1);
}

int main(void)
{
	init(); 
	selectsort();
	print();
	return 0;
}
