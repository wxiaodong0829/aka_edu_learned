#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
        int c,  i, j = strlen(s)-1;
        for (i = 0; i < j ; i++, j-- )
        {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}

char *myitoa(int n, char s[])
{
        int i = 0, sign;
        sign = n;
        if (sign < 0)n = -n;
        do
        {
             s[i++] =  n % 10 + '0';
        }while(n /= 10);
        if (sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
        return s;
}

int main()
{
    int n = 1234;
    char *p, q[20];
   p = myitoa(n,q);

   printf("%s\n", p);
        return 0;
}
