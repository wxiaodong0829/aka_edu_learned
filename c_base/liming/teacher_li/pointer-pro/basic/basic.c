#include <stdio.h>

int g = 100;
int g2 = 100;
int * gp;
int ga;

int main(void)
{
    int * p;
    int a = 0x804a030;

    //a = 100;

    //p = (int *)1234;
    p = (int *)0x804a030;
//    p = (int *)0x8048030;
//    p = p + 1;
//    p = p * 2;
//    p = p - 1;
    // memory access
//    a = *p; 
    *p = 23456;

    int b = *(int *)a;
    printf("b = %d\n", b);

    printf("p = %d\n", (int)p);
    printf("main = 0x%x\n", (int)main);
    printf("&g = 0x%x\n", &g);
    printf("&g2 = 0x%x\n", &g2);
    printf("&gp = 0x%x\n", &gp);
    printf("&ga = 0x%x\n", &ga);
    printf("------------------\n");
    printf("&p = 0x%x\n", &p);
    printf("&a = 0x%x\n", &a);

    return 0;
}
