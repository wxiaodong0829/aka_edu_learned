#include <stdio.h>
#include <ctype.h>
#define N 512

void change(char *str)
{
        int i, j, k;
        char tmp;
        for(i = 0; !isdigit(str[i]); i++)  
                ;
        for(j = i+1; str[j]; j++)
        {
            if(!isdigit(str[j])) 
            {
                tmp = str[j]; 
                for(k = j; k > i; k--)
                        str[k] = str[k-1];
                 str[i] = tmp;
                i += 1;
            }
        }

}
int main(void)
{
    char str[N] = "asdf123dsdfe52dfe41";
    printf("%s\n", str);
    change(str);
    printf("%s\n", str);

    return 0;

}
