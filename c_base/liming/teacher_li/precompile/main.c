//#include <stdio.h>

//extern int printf (__const char *__restrict __format, ...);
//
int printf(const char * fmt, ...);

#define STR     "hello," \
            "precompile\n"

//#define DEBUG
//#define MAX(a, b)   ...

#define U32 unsigned long 
//typedef unsigned long U32;

#define SQUARE(a)   ((a)*(a))
#define MAX(a, b)   ((a) > (b)? (a) : (b))
#define MAX3(a, b, c)   MAX((MAX(a, b)), (c))
//#define MAX3(a, b, c)   (MAX(a, b) > (c)? MAX(a, b) : (c))
//#define MAX3(a, b, c)   ((a) > (b)? (((a) > (c))? (a) : (c)) : (((b) > (c))? (b) : (c)))

#define ISDIGIT(a)  ((a) >= '0' && (a) <= '9' ? 1 : 0)

#define ISUPPER(a)  ((a) >= 'A' && (a) <= 'Z' ? 1 : 0)
#define ISLOWER(a)  ((a) >= 'a' && (a) <= 'z' ? 1 : 0)
#define ISALPHA(a)  (ISUPPER(a) || ISLOWER(a))

#define DIGIT_TO_CHAR(n)     ( (n) < 10 ? ((n) + '0') : ((n) - 10 + 'A') )
#define D_TO_C(n)       ( "0123456789ABCDEF"[n] )

//#define DEBUG   1
#if 1
    //#define PRINT(x)        printf(#x " = %d\n", x)
    #define PRINT(x)        printf("<%s> [%d] %s() "#x " = %d\n",__FILE__, __LINE__, __func__,  x)
#elif DEBUG >= 1
    #define PRINT(x)        printf(#x " = %d\n", x)
#else
    #define PRINT(x)        
#endif

#define MK_ID(n)    i##n

#define G_M(type)     \
    type type##MM(type a, type b)    \
    {   \
        return a > b? a: b; \
    }

G_M(int)
G_M(float)
#define X86     1
#define ARM     2

int test(void)
{
//    int a = 300;

#if CPU == X86
    int a = 300;
#elif CPU == ARM
    int a = 200;
#else
    #error "test is failed"
#endif

#define AAA 100
    PRINT(a);

    return AAA;
}


int main(void)
{
    int a;
    int b[3] = {5, 7, 9};
//    int i1;
    //int MK_ID(100);
    test();
    return 0;
#if DEBUG > 5
#error "main is failed"
#endif

#if 1
//    U32 a;
    a = AAA;
    printf("hello, precompile\n");
   

    printf("in file %s\n" , __FILE__);
    printf("in date %s\n" , __DATE__);
    printf("in time %s\n" , __TIME__);
    printf("line %d: M = %f\n", __LINE__, floatMM(2.3, 3.9));
    printf("line %d: M = %f\n", __LINE__, floatMM(2.3, 3.9));
    printf("M = %d\n", intMM(2, 3));
#endif

#define PI 3.14
#undef PI
#define PI 3.1415
    a = PI * 2;

    a = SQUARE(100+100)*50;

    a = MAX3(10, 20, 30);
    //PRINT(PI);
    PRINT(a);
    test();

    PRINT(2*(a+10));
    PRINT(a/10);
    PRINT(b[1] + b[2]);
    return 0;

//    printf("a = %d\n", a);
    printf("char = %c\n", DIGIT_TO_CHAR(7));

    printf("max is %d\n", MAX(100+50, 200+300));

    printf("result a is %d\n", ISDIGIT('a'));
    printf("result 9 is %d\n", ISDIGIT('9'));

    printf(STR);

    return 0;
}
