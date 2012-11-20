#include <stdio.h>

int n;

int Bubble_sort(int str[n])
{
	int i,j;
	int tmp;
	tmp=str[j-1];

	int flag;
	
	for(i=0;i<n-1;i++)
	{
		flag=0;
		for(j=n-1;j>i;j--)
		{
			if(str[j]<str[j-1])
			{
				tmp = str[j-1];
			        str[j-1] = str[j];
				str[j] = tmp;
				flag = 	1;
			}
		}
		if(!flag)
			return 0;
	}
}

int my_rand(int n,int m)
{
	return rand() % (m - n + 1)+ n;
}

void gen_num(void)
{
	int i;
	for(i = 0;i < 8;i++)
		a[i] = my_rand(1,100);
}

void print_num(void)
{
	int a[i];
	for(i = 0;i < 8;i++)
		printf("%d ",a[i])
	
}

int main(void)
{
	Bubble_sort(num[8]);
    	for(i = 0;i<8;i++)
		 printf("%d\n",num[i]);
	return 0;
}
