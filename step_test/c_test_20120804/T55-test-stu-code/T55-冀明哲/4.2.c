#include<stdio.h>
#include<time.h>
// mao pao pai xu
/*int main()
{
	int i, j, num[10], tmp;
	int flag=0;
	srand(time(NULL));
	for(i=0; i<10; i++)
		num[i]=rand();

		for(i=0; i<10; i++)
		{
			for(j=0; j<9-i; j++)
				if(num[j]>num[j+1])
				{
					tmp=num[j];
					num[j]=num[j+1];
					num[j+1]=tmp;
					flag=1;
				}
				if(flag==0) break;
		}
		for(i=0; i<10; i++)
			printf("%d  ",num[i]);
			printf("\n");
	return 0;
}*/
//xuan ze pai xu
int main()
{
	int i, j, k, num[10], tmp;
	srand(time(NULL));
	for(i=0; i<10; i++)
		num[i]=rand();

		for(i=0; i<10; i++)
		{
			k=i;
			for(j=i+1; j<10; j++)
			{
				if(num[j]<num[k])
					k=j;
			}

			if(k!=i)
			{
				tmp=num[k];
				num[k]=num[i];
				num[i]=tmp;
			}
		}
		for(i=0; i<10; i++)
			printf("%d ",num[i]);
			printf("\n");
}

