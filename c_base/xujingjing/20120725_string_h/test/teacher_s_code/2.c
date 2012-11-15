#include <stdio.h>

char *myitoa(int n, char *strp)
{
    int i, j, flag;
    char tmp;
    char *table = "0123456789";

    //n = -23;
    if((flag = n) < 0)
        n = -n;
    
    i = 0;
    do{
        strp[i++] = table[n % 10];
    }while(n /= 10);
    if(flag < 0) 
        strp[i++] = '-';
    strp[i] = '\0';

    for(--i, j = 0; j <= i; i--, j++){
        tmp = strp[j];
        strp[j] = strp[i];
        strp[i] = tmp;
    }
    return strp;
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
