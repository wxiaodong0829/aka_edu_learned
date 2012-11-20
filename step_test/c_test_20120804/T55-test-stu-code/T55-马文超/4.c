#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[100], tmp;
    int i, j, end;
    printf("putin s:");
    scanf("%s", s);
    for (i = end = strlen(s) - 1; i > 0; i--)
    {
	if (s[i] > s[i - 1])
	{
	    tmp = s[i - 1];
	    for (j = i; i < end; i++)
		s[i - 1] = s[i];
	    s[--end] = tmp;
	} 
    }
    printf("%s\n", s);
    return 0;
}

