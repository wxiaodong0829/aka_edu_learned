#include<stdio.h>
#include<string.h>
#include<ctype.h>

char str[15] = "asd123fgh543df";
int main(void)
{
    int i, j, tmp;
    for(i = strlen(str)- 1; i > 0; i--)
    {
        if(isdigit(str[i]))
        {
            tmp = str[i];
            for(j = i; j < end; j++ )
                str[j] = str[j+1];
            str[end--] = tmp;
        }


    }
    printf("%s\n",str);
    return 0;

}
