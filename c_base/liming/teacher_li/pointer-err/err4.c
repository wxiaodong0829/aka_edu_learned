#include <stdio.h>

#define PRINT(x)    printf("(%s)debug> " #x" = 0x%x (%c)\n",__func__, x, x)

char * getp(int i)
{
//    static char buf[20];
//    char buf[20];
 
    char * buf = malloc(20);

    printf("buf = 0x%x\n", buf);
    if (i == 0)
        strcpy(buf, "Sunday");

    if (i == 1)
        strcpy(buf, "Monday");

    return buf;
}

void b(int a)
{
    char c[8];
    getp(0);
}

void a(void)
{
    b(1);
    getp(0);
}

int main(void)
{
    char * p;
    int i;
    
//    p = getp();
 //   *p = 'a';

    p = getp(0);
    PRINT(p);
    PRINT(*p);
    free(p);

    for (i = 0; i < 20; i++)
    {
        *(p+i) = 'a';
        PRINT(*(p+i));
    }

    //p = NULL;

    //p = getp(0);
    PRINT(p);
    PRINT(*(p+15));
    return 0;

    p = getp(1);
    *p = 'a';
    PRINT(p);
    return 0;

    a();

    p = getp(1);
    //free(p);

    printf("ret = %s\n", getp(0));
    printf("ret = %s\n", getp(1));
    printf("ret = %s, %s\n", getp(0), getp(1));

  //  PRINT(*p);

    return 0;
}
