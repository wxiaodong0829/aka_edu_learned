#include <stdio.h>
#include <string.h>

char *fun(char *str, int len)
{
	int i, j, end;
	char tmp;

	for(end = i = len - 1; i >= 0; i--)
	{
		if(str[i] >= '0' && str[i] <= '9')
		{
			tmp = str[i];
			for(j = i + 1; j <= end; j++)
				str[j - 1] = str[j];
			str[end--]= tmp;
		}
	}
	return str;
}

int main(void)
{
	char str[50] = "asd123fgh543df";

	//	scanf("%s", str);
	printf("str:%s\n", fun(str, strlen(str)));

	return 0;
}
