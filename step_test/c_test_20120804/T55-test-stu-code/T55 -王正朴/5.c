#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *fun(char p[])
{
	int  tmp;
	int i,j,end;

	for(i =end=strlen(p) -1; i >= 0; i--)
	{
		if(isdigit(p[i]))
		{
			tmp =p[i];
		for(j = i; j < end; j++)
			p[j ] = p[j+1];
			p[end--] =tmp;
		}
	}
	return p;

}
int main()
{
	char src[]="asdf123fgh543df";
	char *s;
	s =fun(src);
	printf("%s\n",s);

	return 0;
}
