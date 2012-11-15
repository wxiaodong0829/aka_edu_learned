/*************************************************************************
  > File Name: hello.c
  > Author: wxiaodong
  > Mail  : wxiaodong0829@163.com 
  > 自由  谐作   创造   沟通
  > Created Time: 2012年07月30日 星期一 09时30分54秒
 ************************************************************************/

//#include <stdio.h>
extern int printf(__const char * __restrict __format, ...);
int printf(const char *fmt, ...);
//int printf(char *fmt, ...);
#define STR	"hello, "\
	"precompile\n"

#define PI  3.14			  //不加  ;   
typedef unsigned long u32;    //加  ;   

//#define MAX(a, b) ((a) > (b) ? (a) : (b))                 ,3

#define ISDIGIT(a)  ((a) >= '0' && (a) <='9' ? 1 : 0 )

#if 0
#define ISALPHA(a) {\
	char tmp;\
	if (a >= 'a' && a <= 'z') {\
		tmp = a - 'a';\
		a = tmp;\
	} else if (a >= 'A' && a <= 'Z') {\
		tmp = a - 'A';\
		a = tmp;\
	} else a = a;\
}
#endif

//#define DIGIT_TO_CHAR(n) ((n) + '0')
//#define DIGIT_TO_CHAR(n) ((n) <= 9 ? (n) + '0' : (n) - 10 + 'A')
#define DIGIT_TO_CHAR(n)	("0123456789ABCDEF"[(n)])    //无跳转语句

//#define DEBUG
#ifdef DEBUG
	#define PRINT(n) printf(#n " = %d\n", n); //调试时 用
#else
	#define PRINT(n)     
#endif

// statement 语句（一条，或复合语句）
// 下面的方式是为解决
//	if (echo_flat)
//		ECHO(s);
//	else 
//		gets(s);
//
//
#define ECHO(s) {gets(s); puts(s);}
// 
//	if (echo_flat)
//		{gets(s); puts(s)} ;          // 此处多了一个 分号 ";" else 将被报错
//	else							 // 解决办法：do{}while(0)  此处特意留了分号的位置。
//		gets(s);
//
#define ECHO(s) do {\
	gets(s);\
	puts(s);\
} while (0)\

#if CPU == X86
	int cpu = 300;
#elif CPU == ARM
	int cpu = 200;
#else
#error "failed"
#endif

int main(void)
{
	//printf("hello, \
	//					precompile\n");
	//printf("hello, "\
	//					"precompile\n");

	//	a = PI;
	//	printf(STR);

	//printf("max is %d\n", MAX(100 + 50, 200 + 200));      ,3

	char a = 'c';
	char b = '=';
	ISALPHA(a);
	ISALPHA(b);
	printf("max is %d\n", a);
	printf("max is %c\n", b);

	printf("max is %c\n", DIGIT_TO_CHAR(0));

	PRINT(DIGIT_TO_CHAR(0));
	return 0;
}
