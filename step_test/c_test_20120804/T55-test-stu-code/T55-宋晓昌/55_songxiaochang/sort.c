	#include<stdio.h>
	void sort(char num[],int n)
	{
		int j,k,min;
		int tmp,i;
		for(j=0;j<n;j++)
		{
			 min=j;
			for(k=j+1;k<n;k++)
			{
				if(num[min]>num[k])
				min=k;
			}
			tmp=num[j];
			num[j]=num[min];
			num[min]=tmp;
		}
		for(i=0;i<n;i++)
		{
			printf("%d\t",num[i]);
		}
	}

