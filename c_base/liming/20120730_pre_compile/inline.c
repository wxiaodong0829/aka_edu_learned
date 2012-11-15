/*************************************************************************
    > File Name: inline.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月30日 星期一 18时40分37秒
 ************************************************************************/

//#include <stdio.h>
extern int printf(__const char *fmt, ...);

#define PRINT(n) printf(#n" = %d\n", n)

#define add_marc(a,b) ((a) + (b) + (a))

inline int add(int a, int b)
{
	return a + b + a;
}
//struct std {       //sizeof(struct std)   12
//	int a;
//	char *c;
//	short b;        //
//	short d;		//与b 的空间对齐
//}st;
//struct std {       //能对齐的，就对齐，不能对齐就补齐
//	int a;
//	char *c;
//	short b;
//}st;
struct std {       //能对齐的，就对齐，不能对齐就补齐
	char a;
	char b;
	char c;
}st;
int main(void)
{
	int c = 1;
	int b = 2;
	PRINT(sizeof(struct std));
	PRINT(add_marc(++c,b));
	c = 1;
	b = 2;
	PRINT(add(++c, b));
	
	return 0;
}
