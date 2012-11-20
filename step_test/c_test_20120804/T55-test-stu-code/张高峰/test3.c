#include<stdio.h>
#include<time.h>

#define N 5
int arr[N][N];

void init()
{
	int i,j;
	srand(time(NULL));
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			arr[i][j]=rand()%N;

}

void print()
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			if(j==(N-1))
			{
				printf("%d ",arr[i][j]);
				printf("\n");
			}
			else
				printf("%d ",arr[i][j]);
		}
	printf("\n");
		
}

void lineswap(int g,int i,int j)
{
	int tmp;
	tmp=arr[g][i];
	arr[g][i]=arr[g][j];
	arr[g][j]=tmp;
}

void lineselectsort(int g)
{
	int i,j;
	for(j=1;j<N;j++)	
		for(i=j;i>0;i--)
			if(arr[g][i]<arr[g][i-1])
				lineswap(g,i,i-1);
}


void linesort()
{
	int i;
	for(i=0;i<N;i++)
	{
		lineselectsort(i);
	}	
}

void colswap(int g,int i,int j)
{
	int tmp;
	tmp=arr[i][g];
	arr[i][g]=arr[j][g];
	arr[j][g]=tmp;
}

void colselectsort(int g)
{
	int i,j;
	for(j=1;j<N;j++)	
		for(i=j;i>0;i--)
			if(arr[i][g]<arr[i-1][g])
				colswap(g,i,i-1);
}

void colsort()
{
	int i;
	for(i=0;i<N;i++)
	{
		colselectsort(i);
	}
}

int main(void)
{
	init();
	printf("line sort:\n");
	linesort();
	print();
	printf("col sort:\n");
	colsort();
	print();
	return 0;
}
