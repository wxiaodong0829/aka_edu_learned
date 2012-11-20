#include <stdio.h>
#include <time.h>
int num[10];

void init (int s[],int n)
{
	int i;
	srand(time(NULL));
	for(i =0; i < n; i++)
		s[i] =rand()%100;
}
void show(int s[],int n)
{
	int i;
	for(i = 0;i < n; i++)
		printf("%d\t",s[i]);
}
void firstsort(int s[],int n)
{

	int i ,j;
	int tmp;
	for(i = 0; i < n ;i++)
	{
		for(j = 0; j < n -1 -i; j++)
		{
			if(s[j] > s[j + 1])
			{
				tmp =s[j+1];
				s[j+1] =s[j];
				s[j] =tmp;
			}
//			printf("%d\t",s[j]);
		}
		printf("%d\t",s[i]);
	}
	printf("\n");
}
void sort(int s[], int n)
{
	int i,j,tmp,k;
	int max;
	k = n-1;
	for(i =0; i < n ; i++)
	{
		max =i;
		for(j = i+1; j < n; j++)
		{
			if(s[max]  < s[j])
				max =j;
		}
	{
		tmp =s[k];
		s[k] =s[max];
		s[max] =tmp;
	}
	printf("%d \t",s[i]);
	}
	printf("\n");
}
int main ()
{
	init(num,10);
	show(num,10);
	printf("\n");
	firstsort(num,10);
	sort(num,10);

	return 0;
}
