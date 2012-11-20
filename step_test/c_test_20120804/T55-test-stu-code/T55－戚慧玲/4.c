#include <stdio.h>
#include <string.h>

#define N 100

void max(char str[N])
{
	int j,i;

	int n = strlen(str);
	char max = str[0];
	
	for(i = 1;i < n;i++)
	{
		if(str[i] > max)
			max = str[i];
	}

	for(j = i;j >= 0;j--)
	{
		str[j] = str[j-1];
	}
	
	str[0] = max;

	printf("Please input:%c\n",max);

	for(i = 0;i < n;i++)
		printf("%c",str[i]);
	printf("\n");
//	return 0;
}


int  main(void)
{
	char ss[N] = "studentz";

	max(ss);
	return 0;
}
