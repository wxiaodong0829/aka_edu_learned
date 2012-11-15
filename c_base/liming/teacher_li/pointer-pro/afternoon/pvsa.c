#include <stdio.h>

//char * p1 = "hello";
//char p2[10] = "hello";

int main(void)
{
  char * p1 = 0x8048600; // 0x8048600: "hello";
  char p2[] = "hello world";     // strcpy(p2, "hello");

    printf("p1 = 0x%x\n", (int)p1);
    printf("p2 = 0x%x\n", (int)p2);

    printf("&p1 = 0x%x\n", (int)&p1);
    printf("&p2 = 0x%x\n", (int)&p2);
    printf("&p2[9] = 0x%x\n", (int)&p2[7]);

    printf("char at 0x804a018 is %c\n", *(char *)0x804a018);
    printf("char at 0x804a019 is %c\n", *(char *)0x804a019);
    return 0;
}
