#include <stdio.h>

char *myitoa(int n, char *str)
{
    int i, j, k;
    char tmp;
    if((k = n) < 0)
	n = -n;
    i = 0;
    do
    {
	str[i++] = n % 10 + '0';
    }
    while(n /= 10);
    if(k < 0) 
	str[i++] = '-';
    str[i] = '\0';
    for(--i, j = 0; j <= i; i--, j++)
    {
	tmp = str[j];
	str[j] = str[i];
	str[i] = tmp;
    }
    return str;
}

int main(void)
{
    int n;
    char str[10];
    printf("Input n:");
    scanf("%d", &n);
    printf("itoa:%s\n", myitoa(n, str));
    return 0;
}
