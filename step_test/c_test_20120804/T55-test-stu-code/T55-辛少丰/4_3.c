#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 5 
#define N 5 
int arr[M][N];
void my_rand(int arr[M][N])
{
	int i, j;
	srand(time(NULL));
	for (i=0; i<M; i++) {
		for (j=0; j<N; j++) 
	        	arr[i][j] = rand()%100;
	}
}
void print_num(int arr[M][N])
{
	int i, j;
	for (i=0; i<M; i++) {
		for (j=0; j<N; j++)
			printf("%3d", arr[i][j]);
		printf("\n");
	}
	printf("\n");
}
#if 0
void select_num(int arr[M][N], int n)
{
	int i, j, tmp;
	for (i=1; i<N; i++) {
		tmp = arr[i];
		for (j=i-1; j>=0 && tmp<arr[j]; j--) {
			if (tmp<arr[j]) {
				arr[j+1] = arr[j];
			}
		}
		arr[j+1] = tmp;
	}
}
#endif
int main()
{
	my_rand(arr);
	print_num(arr);
	printf(".......11111111111111\n");
	//select_num(arr, 5);
	//print_num(arr);
	printf(".......22222222222222\n");
	//select_num(arr, 1);
	//print_num(arr);
	return 0;
}
