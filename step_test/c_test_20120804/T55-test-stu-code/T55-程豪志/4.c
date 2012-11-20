#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char src[100], tmp;
    int i, j, end;

    printf("Input src:");
    scanf("%s", src);

    for(i = end = strlen(src) - 1; i >= 0; i--)
    {
	if (src[i] > src[i + 1])
	{
	    tmp = src[i - 1];
	    for(j = i; i < end; i++)
		src[i - 1] = src[i];
	}
	    src[--end] = tmp;
	
    }
    printf("src:%s\n", src);
    return 0;
}
