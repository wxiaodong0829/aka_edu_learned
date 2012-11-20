#include <stdio.h>
#include <string.h>

char *fun(char s[])
{
    char tmp;
    int len = strlen(s), i, j, state = len - 1;;
    for(i = len - 1; i >= 0; i--)
    {
        if (!isalpha(s[i]))
        {
            tmp = s[i];
            for (j = i; j < state; j++)
            {
                    s[j] = s[j+1];
            }
            s[state--] = tmp;
        }
           
    }
    return s;
}
int main()
{
    char str[] = "asd123fgh543df";
    char *p;

    printf("%s\n", str);
    p =  fun(str);
    printf("%s\n", p);
    return 0;
}
