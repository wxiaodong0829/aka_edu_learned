#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 100
char * fun(char s[])
{
    int i, j, end;
    char tmp;

    for(i = end = strlen(s) - 1; i >= 0; i--)
    {
	if(isdigit(s[i]))
	{
	    tmp = s[i];
	    for(j = i; i < end; i++)
		s[i] = s[i + 1];

	    s[end--] = tmp;
	}

    }
    return s;
}
int main(void)
{
    char s[N];
    char *p;
    int i;
    printf("input s[N]:");
    scanf("%s", s);
    p = fun(s);
    for (i = 0; i < strlen(s); i++)
	printf("%c", *(p+i));
    printf("\n");
    return 0;
}
