#include <stdio.h>
#include <time.h>

#define N 10

void swap(int *a, int *b) 
{ 
	int tmp; 
	tmp=*a, *a=*b, *b=tmp;
}

void sort(int s[])
{
	int i, j, k;

	for(i=1; i<=N; i++)
		for(j=0; j<N-i; j++)
		{
			if(s[j] > s[j+1])
			    swap(&s[j], &s[j+1]);

			for(k=0; k<N; k++)
        		printf("%d   ", s[k]);
        	printf("     ##\n");
		}
}

void c_sort(int s[])
{
	int i, j, k;

	for(i=0; i<N-1; i++)
		for(j=i+1; j<N; j++)
		{
			if(s[i] > s[j])
			    swap(&s[i], &s[j]);

            for(k=0; k<N; k++)
           		printf("%d   ", s[k]);
           	printf("    ##\n");
		}
}

int main(int argc, char *argv[])
{
	int num[N], i;

	srand(time(NULL));
	for(i=0; i<N; i++)
		num[i] = rand()%100;

    for(i=0; i<N; i++)
		printf("%d   ", num[i]);
	printf("\n\n");

	sort(num);
//	c_sort(num);

    for(i=0; i<N; i++)
		printf("%d   ", num[i]);
	printf("\n");

	return 0;
}
