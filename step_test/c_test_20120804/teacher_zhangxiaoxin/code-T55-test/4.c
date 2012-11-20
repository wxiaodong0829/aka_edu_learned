#include <stdio.h>
#include <string.h>

void find_max(char *str, int len)
{
	int i, j;
	int max_flag;
	char c;

	for(i = 0; i < len; i++)
	{
		max_flag = i;
		for(j = 0; j < len; j++)
		{
			if(str[j] > str[i])	
				max_flag = j;
		}
	}
	printf("max_flag = %d\n", max_flag);

	c = str[max_flag];
	for(i = max_flag; i >= 0; i--)
	{
		str[i] = str[i - 1];
	}
	str[0] = c;
}

int main(int argc, char *argv[])
{
	char str[] = "chyab";

	printf("strlen(str) = %d\n", strlen(str));
	find_max(str, strlen(str));
	printf("%s\n",str);

	return 0;
}

