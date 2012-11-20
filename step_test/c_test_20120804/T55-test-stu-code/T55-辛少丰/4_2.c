#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int num[N];
void my_rand(int num[])
{
	int i;
	srand(time(NULL));
	for (i=0; i<N; i++) {
		num[i] = rand()%100;
	}
}
void print_num(int num[])
{
	int i;
	for (i=0; i<N; i++) {
		printf("%3d", num[i]);
	}
	printf("\n");
}
void maopao_num(int num[])
{
	int i, j, tmp;
	for (i=0; i<N-1; i++) {
		for (j=0; j<N-i-1; j++) {
			if (num[j]>num[j+1]) {
				tmp = num[j]; 
				num[j] = num[j+1];
				num[j+1] = tmp;
			}
		}
	}
}
void select_num(int num[])
{
	int i, j, tmp;
	for (i=1; i<N; i++) {
		tmp = num[i];
		for (j=i-1; j>=0 && tmp<num[j]; j--) {
			if (tmp<num[j]) {
				num[j+1] = num[j];
			}
		}
		num[j+1] = tmp;
		//print_num(num);
	}
}
int main()
{
	my_rand(num);
	print_num(num);
	printf(".......maopao\n");
	maopao_num(num);
	print_num(num);
	printf(".......select\n");
	my_rand(num);
	print_num(num);
	select_num(num);
	print_num(num);
	return 0;
}
