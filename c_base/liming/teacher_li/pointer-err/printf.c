#include <stdio.h>

int myprintf(const char * fmt, ...)
{
    

}

int test(int a, int b, int c)
{
    printf("&a = 0x%x\n", &a);
    printf("&b = 0x%x\n", &b);
    printf("&c = 0x%x\n", &c);

    return 0;
}

typedef int *   va_list;
#define va_start(ap, A)     ap = &(A);
#define va_arg(ap, T)   *(T *)(ap = (char *)ap + sizeof(T))
#define va_end(ap)      ap = (void *)0

int max(int len, ...)
{
    int i;
    //int * p = &len;
    va_list p;

//    p = &len;
    va_start(p, len);

    printf("first para: %d\n", len);

    for (i = 0; i < len; i++)
    {
        char val;

        val = va_arg(p, char);
        printf("para %d = %c\n", i, val);
    }
#if 0
    printf("*1 = %d\n", *p++);
    printf("*2 = %d\n", *p++);
    printf("*3 = %d\n", *p++);
#endif

    va_end(p);

    return 0;
}

int main(void)
{
    int a;
    a = 1 + 3 & 4;
    printf("a = %d\n", a);
    return 0;

    test(1, 2, 3);
    printf("hello\n");
    printf("hello %d\n", 100);
    printf("hello %c %d\n", 'a', 200);

    max(3, 'a', 'c', 'z');
    return 0;
    max(3, 100, 200, 300);
    max(2, 100, 500);
    max(1, 100);
    max(7, 100, 200, 300, 10, 20, 30, 50);

    return 0;
}
