#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(void *p, int len)
{
	int *start = p, i, j, tmp, pos;

	for(i = 0; i < len - 1; i++)
	{
		pos = i;
		for(j = i + 1; j < len; j++)
			if(start[pos] > start[j])
				pos = j;
		if(pos != i)
		{
			tmp = start[pos];
			start[pos] = start[i];
			start[i] = tmp;
		}
	}
}
void init_arr(int (*par)[5], int row)
{
	int i, j;

	srand(time(NULL));
	for(i = 0; i < row; i++){
		for(j = 0; j < 5; j++)
			par[i][j] = rand() % 100;
	}
}
void print_arr(int (*par)[5], int row)
{
	int i, j;

	for(i = 0; i < row; i++){
		for(j = 0; j < 5; j++)
			printf("%d ", par[i][j]);
		printf("\n");
	}
}
int main(void)
{
	int arr[5][5], i;
	
	init_arr(arr, 5);
	print_arr(arr, 5);

	printf("Sort by one row...\n");
	for(i = 0; i < 5; i++)
		sort(arr[i], 5);
	print_arr(arr, 5);

	printf("Sort...\n");
	sort(arr, 5 * 5);
	print_arr(arr, 5);


	return 0;
}
