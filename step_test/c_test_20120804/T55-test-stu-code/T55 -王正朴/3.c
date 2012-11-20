#include <stdio.h>
#include <time.h>

void init(int a[][5])
{
	int i,j;
	srand(time(NULL));
	for(i =0; i < 5; i++)
		for(j = 0; j <5; j++)
			a[i][j] =rand()%100;

}
void show(int a[][5])
{
	int i,j;
	for(i =0; i < 5; i++)
	{
		for(j = 0; j <5; j++)
			printf("%d \t ",a[i][j]);
		printf("\n");
	}
}
void selectsort(void *a)
{
	int i,j,max;
	int *s =a;
	int tmp;
	int k =4;
	for(i = 0; i <5; i++)
	{
		max =i;
		for(j = i+1; j < 5; j++)
		{
			if(s[max] < s[j])
				max =j;
		}
		{
			tmp =s[k];
			s[k] = s[max];
			s[max] =tmp;
		}

		printf("%d\t",s[i]);
	}
	printf("\n");

}
int main ()
{
	int arr[5][5];
	init(arr);
	show(arr);
	printf("\n");


	return 0;
}
