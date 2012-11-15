#include <stdio.h>
void test2(void)
{
    int * p;

    printf("p = 0x%x\n", (int)p);
    printf("&p = 0x%x\n", (int)&p);
    *p = 100;
    printf("ok\n");
}

void test(void)
{
    int * p = (int *)0;
    int a[2];

    // .....
    printf("&a[] = 0x%x \n", (int)a);
    printf("&a[-10] = 0x%x \n", (int)(a-10));
    //a[-10] = 0x804a080;

    printf("p = 0x%x\n", (int)p);
    //    *p = 100;
    //   printf("ok\n");

    a[-10] = 0x804a090;
    test2();
}

void f(const int b)
{
    b = 100;

    return;
}

int main(void)
{
    const char * p;
    char * const p2;
    const int a = 100;
    int const a2 = 100;
    const int b = 200;

    f(b);
    printf("b = %d\n", b);

    p = (const char *)'a';
    p = p + 1;
    p++;
//    *p = 'a';
    
    *p2 = 'a';

//    p2 = 'a'; 

    test();
    //    test2();
    return 0;
}
