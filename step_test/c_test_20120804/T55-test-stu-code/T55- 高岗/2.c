#include <stdio.h>
#include <time.h>
int mysort(int ch[], int n)
{
	int i, j, k, tmp;
	for(i = 0; i < n - 1; i++)
	{
		k = i;
		for(j = i + 1; j < n; j++)
			if(ch[j] < ch[k])
				k = j;
		if(k != i)
		{
			tmp = ch[i];
			ch[i] = ch[k];
			ch[k] = tmp;
		}
	}	
}

int main()
{
	int num[10], i, j ,tmp, flag;
	int n = 10;
        srand(time(NULL));

	for (i = 0; i < n; i++)
		num[i] = rand()%100;

	for(i = 0; i < n - 1; i++)
	{
		flag = 0;
		for(j = n - 2; j >= i; j--)
			if(num[j] > num[j + 1])
			{
				tmp = num[j + 1];
				num[j + 1] = num[j];
				num[j] = tmp;
				flag = 1;
			}
		if(!flag)
			break;
	}


	for (i = 0; i < 10; i++)
	{
		printf("%d  ", num[i]);
	}
	printf("\n");

	mysort(num, n);
	for (i = 0; i < 10; i++)
	{
		printf("%d  ", num[i]);
	}
	printf("\n");



	return 0;
}
