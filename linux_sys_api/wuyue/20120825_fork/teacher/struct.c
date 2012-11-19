#include <stdio.h>

#pragma pack(1)
struct t1
{
    int i;
    char c1;
    short s;
    char c2;
};
#pragma pack()
struct t2
{
    int i;
    char c1;
    short s;
    char c2;
};

int main(void)
{
    short i;
    struct t1 v;
    struct t2 v2;
    //short s;

    printf("size : %d\n", sizeof(struct t1));
    printf("size : %d\n", sizeof(struct t2));
    
    printf("v : %p\n", &v);
    printf("i : %p\n", &i);
    //printf("s : %p\n", &s);
    printf("v2 : %p\n", &v2);

    return 0;
}
