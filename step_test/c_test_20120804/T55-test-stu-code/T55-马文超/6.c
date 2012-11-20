#include <stdio.h>

char *myitoa(int n, char *p)
{
    int i, j, flag;
    char tmp;

    if((flag = n) < 0)
	n = -n;

    i = 0;
    do{
	p[i++] = n % 10 + '0';
    }while(n /= 10);
    if(flag < 0) 
	p[i++] = '-';
    p[i] = '\0';

    for(--i, j = 0; j <= i; i--, j++){
	tmp = p[j];
	p[j] = p[i];
	p[i] = tmp;
    }
    return p;
}

int main(void)
{
    int n;
    char str[15];

    printf("Input n:");
    scanf("%d", &n);

    printf("itoa:%s\n", myitoa(n, str));
    return 0;
}
