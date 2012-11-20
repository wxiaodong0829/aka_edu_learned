	#include<stdio.h>
	#include<time.h>
	void myrand()
	int i;
	srand(time(NULL));
	for(i=0;i<10;i++)
	{
		num[i]=rand()%100;
		printf("%d\t",num[i]);
	}
	printf("\n");
