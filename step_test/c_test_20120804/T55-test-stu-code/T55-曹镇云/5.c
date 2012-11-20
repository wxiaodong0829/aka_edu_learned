#include<stdio.h>
#include<string.h>
#include<ctype.h>

char arr_a[100];
char arr_b[100];

char *fun(char str[])
{
        char c;
    int i, a, b, len;
    len=strlen(str);
    for(i=0, a=0, b=0; i<len; i++)
    {
        c=str[i];
        if(isdigit(c))  arr_a[a++]=c;
        else if(isalpha(c))  arr_b[b++]=c;
    }
    arr_a[a]='\0';
    arr_b[b]='\0';

    strcat(arr_b, arr_a);

    return arr_b;
}
int main(void)
{
    char str[]="asd123fgh543df";

    fun(str);
    printf("%s\n", arr_b);

    return 0;

}

