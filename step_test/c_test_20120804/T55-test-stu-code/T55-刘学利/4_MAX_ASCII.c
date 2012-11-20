#include <stdio.h>
#include <string.h>

void find_max_ascii(char *s)
{
	int i = 0, flag = 0;
	char c = s[i];
	while(s[++i])
	{
		if(s[i] > c)
		{
			c = s[i];
			flag = i;
		}
	}
	while(flag > 0)
	{
		s[flag] = s[flag-1];
		flag--;
	}
	s[0] = c;
	printf("%s\n", s);
}

int main(int argc, char *argv[])
{
	char str[] = "chyab";
	find_max_ascii(str);

	return 0;
}
