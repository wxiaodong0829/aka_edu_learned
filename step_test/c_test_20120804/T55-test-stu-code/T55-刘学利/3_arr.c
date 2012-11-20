#include <stdio.h>
#include <stdlib.h>

#define N 5

int arr[N][N];

void display()
{
	int i, j; 
	for(i = 0; i < N; i++)
	{
	  for(j = 0; j < N; j++)
		  printf("%4d", arr[i][j]);
	  printf("\n");
	}
}

void init()
{
	int i, j;
	srand(time(NULL));
	for(i = 0; i < N; i++)
	  for(j = 0; j < N; j++)
		arr[i][j] = rand()%100;
}

void swap(int s, int i, int j)
{
	int tmp;
	tmp = arr[s][i];
	arr[s][i] = arr[s][j];
	arr[s][j] = tmp;
}
void sort(int i, int end)
{
	int j, k;
	  for(j = 0; j < end; j++)
		for(k = 0; k < end-1; k++)
		  if(arr[i][k] > arr[i][k+1])
			swap(i, k, k+1);
}

int main(int argc, char *argv[])
{
	int i = 0;
	init();
	display();
	printf("\n");
	for(i = 0; i < N; i++)
	  sort(i, 5);

	display();

	return 0;
}
