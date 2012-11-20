#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *fun(char *str, int len)
{
	int i, tmp;
	for(i = len-1; i>0; i--)
    {
		if(!isalpha(str[i]))
			continue;
		if(isalpha(str[i]))
		{
			tmp = str[i];
			for(j=i; j>0; j--)
			{
				if(!isalpha(str[j]))
				{

				}
			}
		}
	}

	return str;
}

int main(int argc, char *argv[])
{
	char str[] = "abd879how9jh2h";

	fun(str, strlen(str));

	printf("%s\n", str);

	return 0;
}
