#include <stdio.h>
#include <string.h>

void fun(char *s)
{
	int i, j,  tmp, len  = strlen(s);
	for(i = len -1; i >= 0; i--)
	  if(s[i] >= '0' && s[i] <= '9')
	  {
		  len--;
		  tmp = s[i];
		  for(j = i; j < len; j++)
			s[j] = s[j+1];
		  s[j] = tmp;
	  }
	printf("%s\n", s);
}

int main(int argc, char *argv[])
{
	char s[] = "asd123gfh456sjd";
	fun(s);
	return 0;
}
