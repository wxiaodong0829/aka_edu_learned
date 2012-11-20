#include <stdio.h>
#define MAX 512 

void change(char *str)
{
    int i, flag = 0;
    char tmp;

    for((i = 1)&&(str[i]); str[i]; i++)
        if(str[i] > str[flag]) 
                flag = i;
    tmp = str[flag];
    for(i = flag; i > 0; i--)
        str[i] = str[i-1];
    
    str[0] = tmp;
            
}

int main(void)
{
    char str[MAX] = "chyab";
    change(str);
    printf("%s\n", str);

    return 0;
}
