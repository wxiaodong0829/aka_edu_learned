#include <stdio.h>
#include <string.h>

int main(void)
{
    char src[] = "    Today    is   a    wonderful day!";
    char dest[5][10], *token, *begin;
    int i;

    for(i = 0, begin = src; (token = strtok(begin, " ")); begin = NULL)
        strcpy(dest[i++], token);

    for(i = 0; i < 5; i++)
        printf("dest[%d] = %s\n", i, dest[i]);
    return 0;
}
