#include<stdio.h>
#include<string.h>

int main(void)
{
    char str[]={"chyab"};

    printf("%s\n", str);

    char tmp=str[0];
    int i, j=0, len;

    len=strlen(str);

    for(i=1; i<len; i++)
    {
        if (tmp<str[i])
        {
            tmp = str[i];
            j++;
        }
    }

    for(i=j-1; i>=0; i--)
    {
        str[i+1] = str[i];
    }

    str[0] = tmp;
    printf("%s\n", str);

    return 0;


}
