#include <stdio.h>

int add(int a, int b)
{
    return a+b;
}

int sub(int a, int b)
{
    return a-b;
}


int mul(int a, int b)
{
    return a*b;
}


int dev(int a, int b)
{
    return a/b;
}

int main(void)
{
    int (*pf)(int , int);
    char ch;
    int a, b, r;
    ch = getchar();
    switch(ch){
        case '+':
            pf = add;
            break;
        case '-':
            pf = sub;
            break;
        case '*':
            pf = mul;
            break;
        case '/':
            pf = dev;
            break;
        default:
            break;
    }
    scanf("%d %d", &a, &b);
    r = pf(a , b);
    printf("%d\n", r);

}
