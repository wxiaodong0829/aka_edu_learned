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

void bsort()
{
	int i,j;
	for(i=1;i<N;i++)
		for(j=0;j<N-i;j++)
			if(num[j]>num[j+1])
				swap(j,j+1); 
}

int main(void)
{
	init(); 
	bsort();
	print();
	return 0;
}
