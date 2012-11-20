#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 100

char *fun(char str[N])
{
/*	int begin,i,j,end;
 	begin == 0;
	char digit;
	int n = strlen(str);
	
	for(i = 0;i < n;i++)
	{
		if(isdigit(str[i]))
		{		
		
			digit = str[i];

		

		for(j=i;i<n-1;i++)
		
			str[i] = str[i+1];
		str[begin++] = digit;
		}

	}
*/
	int i,j,end;
	char digit;

	int n = strlen(str);

	for(i = end = n-1;i>=0;i-- )
	{
		if(isdigit(str[i]))
		{
			digit = str[i];
			for(j = i;i < end;i++)
				str[i] = str[i+1];
			str[end--] = digit;
		}
	}





	for(i = 0;i < n;i++)
		printf("%c",str[i]);
	printf("\n");
}

char main(void)
{
	char ss[N] = "qi88hui08ling19";
	int i;
	int n = strlen(ss);
	for(i = 0;i <n;i++)
		printf("%c",ss[i]);
	printf("\n");
	fun(ss);
}
