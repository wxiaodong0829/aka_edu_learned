#include <stdio.h>
#include <string.h> 
#define N 32

void reverse(char *s)
{
     int i, j, n=strlen(s), tmp;
     for (i=0, j=n-1; i<j; i++, j--)
         tmp = s[i], s[i] = s[j], s[j] = tmp;
}
void dollars(char *dest, char const *src)
{
    int len, i, j, count = 1, flag = 4;
    len = strlen(src);
    if(len ==1)
    {           
            dest[0] = src[0];
            dest[1] = '0';
            dest[2] = '.';
            dest[3] = '0';
            dest[4] = '$';
            dest[5] = '\0';
    }
    if(len ==2)
    {           
            dest[0] = src[1];
            dest[1] = src[0];
            dest[2] = '.';
            dest[3] = '0';
            dest[4] = '$';
            dest[5] = '\0';
    }
    if(len > 2)
    {
        dest[0] = src[len-1]; 
        dest[1] = src[len-2];
        dest[2] = '.';
        j = 3;
        for(i = len-3; src[i]; i--)
        {
            if(count%flag==0)
            {
               dest[j++] = ',';
               count = 1; 
            }
             dest[j++] = src[i]; 
             count += 1; 
        }
        dest[j++] = '$';
        dest[j] = '\0';
    
    }
    reverse(dest);

}
int main(void)
{
    char src[N];
    char dest[N];
    scanf("%s", src);
    dollars(dest, src);
    printf("%s\t%s\n", src, dest);
                    

}







