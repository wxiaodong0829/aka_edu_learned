#include<stdio.h>
#include<string.h>
char str[100];

char *myitoa(int n, char *p)
{
    int i=0, l, r, tmp;
    int mk;

    do{

       p[i++] = n%10 + '0';

    }while((n/=10)>0);

    p[i] = '\0';

    mk=strlen(p);
    for(l=0, r=mk-1; l<=r; l++,r--)
    {
        tmp=p[l]; 
        p[l]=p[r];
        p[r]=tmp;
    }
}

int main(void)
{
    int a;
    a=15453;

    myitoa(a, str);
    printf("%s\n", str);

    return 0;
    
}

