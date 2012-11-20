#include <stdio.h>
#include <string.h>
#include <ctype.h>

int *fun(char src[])
{
    int i, j, tmp, end;
    for(i = end = strlen(src) - 1; i >= 0; i--)
    {
	if (isdigit(src[i]))
	{
	    tmp = src[i];
	    for(j = i; i < end; i++)
		src[i] = src[i + 1];

	    src[end--] = tmp;
	}
    }
    return src;
}
int main(void)
{
    char *p;
    char src[100], tmp;
    int i, j, end;
    printf("Input src:");
    scanf("%s", src);

    p = (char *)fun(src);

    printf("src:%s\n", src);
    return 0;
}
