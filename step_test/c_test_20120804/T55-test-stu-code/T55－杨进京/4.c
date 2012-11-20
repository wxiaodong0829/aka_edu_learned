#include <stdio.h>

void maxc(char str[])
{
    int i, j;
    char p = str[0];

    for (i = 1; str[i] != '\0'; i++)
    {
   if (str[i] > p)
        {
        p = str[i];
        j = i;
        }
    }
    printf("max[%d] = %c\n", j, p);
    
    for (i = j; i >= 0; i--)
        str[i] = str[i-1];
    str[0] = p;

    for (i = 0; str[i]; i++)
        printf("%c ", str[i]);
    printf("\n");
}

int main()
{
    char str[] = "chyab";
    maxc(str);
        return 0;
}

