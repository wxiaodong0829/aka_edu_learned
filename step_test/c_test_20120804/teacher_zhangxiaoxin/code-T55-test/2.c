#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void init_num(int *num, int len)
{
	int i;

	srand(time(NULL));

	for(i = 0; i < N; i++)
	{
		num[i] = rand() % 100;
	}
}

void print_num(int *num, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		printf("%d  ", num[i]);
	}
	printf("\n");
}

void bubble_sort(int *num, int len)
{
	int i, j;
	int tmp;

	for(i = 0; i < len - 1; i++)
	{
		for(j = 0; j < len - i - 1; j++)
		{
			if(num[j] > num[j + 1])
			{
				tmp = num[j + 1];
				num[j + 1] = num[j];
				num[j] = tmp;
			}
		}
	}
}

void selection_sort(int *num, int len)
{
	int i, j;
	int min_flag;
	int tmp;

	for(i = 0; i < len - 1; i++)
	{
		min_flag = i;;
		for(j = i + 1; j < len; j++)
		{
			if(num[j] < num[min_flag])	
			{
				min_flag = j;
			}
		}
		//printf("min_flag %d\n", min_flag);

		if(min_flag != i)
		{
			tmp = num[min_flag];
			num[min_flag] = num[i];
			num[i] = tmp;
		}
	}
}

int main(int argc, char *argv[])
{
	int num[N];

	init_num(num, N);
	print_num(num, N);
	bubble_sort(num, N);
	printf("After bubble:\n");
	print_num(num, N);

	printf("************************************\n");

	init_num(num, N);
	print_num(num, N);
	selection_sort(num, N);
	printf("After selection:\n");
	print_num(num, N);

	return 0;
}
