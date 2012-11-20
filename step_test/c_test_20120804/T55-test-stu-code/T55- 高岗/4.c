#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "chyab", tmp;
	int i, k;

	tmp = str[0];
	for(i = 1; str[i] != '\0'; i++)
	{
		if(tmp < str[i])
		{
			tmp = str[i];
			k = i;
		}
	}
	for(i = k; i >= 0; i--)
		str[i] = str[i -1];
	str[0] = tmp;

	printf("%s\n", str);
	return 0;
}
