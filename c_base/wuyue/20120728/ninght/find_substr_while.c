#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main(void)
{
	int num = 1, i= 0, max = 0, k;
	char s[MAX];
	scanf("%s", s);

	while(s[i])
	{	
		if(s[i] == s[++i])
			num++; 
		else
		{
			if(num > max)
			{
				k = i-num;
				max = num;
			}
			num = 1;
		}
	}
	printf("%d, %d\n", k, max);
	for(i = k; i < k+max; i++)
	  printf("%c", s[i]);
	printf("\n");
	return 0;
}
