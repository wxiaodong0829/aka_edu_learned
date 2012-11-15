# 1 "inline.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "inline.c"
# 10 "inline.c"
extern int printf(__const char *fmt, ...);





inline int add(int a, int b)
{
 return a + b + a;
}
# 31 "inline.c"
struct std {
 char a;
 char b;
 char c;
}st;
int main(void)
{
 int a = 1;
 int b = 2;
 printf("sizeof(struct std)"" = %d\n", sizeof(struct std));
 printf("add_marc(a++,b)"" = %d\n", ((a++) + (b) + (a++)));
 a = 1;
 b = 2;
 printf("add(a++, b)"" = %d\n", add(a++, b));

 return 0;
}
