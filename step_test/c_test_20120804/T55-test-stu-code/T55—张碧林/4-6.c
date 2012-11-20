#include <stdio.h>
#include <string.h>
#define N 48
void reverse(char s[])
{
    int i, j, n=strlen(s), tmp;
    for (i=0, j=n-1; i<j; i++, j--)
        tmp = s[i], s[i] = s[j], s[j] = tmp;
}
char *itoa(int n, char *p)
{
    int i=0, sign; 
    char c;
    if ((sign=n) < 0)
            n = -n;
    do {
        c = n % 10;
        p[i++] = c + '0';
        
    } while ((n/=10) > 0);
    if (sign < 0) p[i++] = '-';
    p[i] = '\0';

    reverse(p);

    return p;
}
int main()
{
    char str[N];
    itoa(-15568, str);
    printf("%s\n", str);
    return 0;
}
