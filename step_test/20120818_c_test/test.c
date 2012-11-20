/*************************************************************************
    > File Name: test.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月18日 星期六 10时16分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"

void abc(char *p)
{
	int i, j;
	for (i = j = 0; *(p + i) != '\0'; i++)
		if (*(p + i) < 'n') {
			*(p + j) = *(p + i);
			j++;
		}
	*(p + j) = '\0';
}
struct st_t {
	int status;
	short *pdata;
	char errstr[32];
};

typedef struct {
	int a;
	int b;
} node;
int foo(int a[10], char b[10], node c, node d[10])
{
	PRINT(sizeof(a));
	PRINT(sizeof(b));
	PRINT(sizeof(c));
	PRINT(sizeof(d));
	return 0;
}
int main(void)
{
#if 0
	long a;
	printf("%d\n", sizeof a);

//11
	char *p = "hello!";
	char p1[] = "hello!";
	void *p2 = malloc(100);
	PRINT(sizeof(p));
	PRINT(sizeof(p1));
	PRINT(sizeof(p2));

//10
	int a[10];
	char b[10];
	node c;
	node d[10];
	foo(a, b, c, d);

//9
	int i = 0;
	while(1) {
		printf("*");
		i++;
		if (i < 3) break;
	}
	printf("\n");

//8
	struct st_t st[16];
	char *p = (char *)(st[2].errstr + 32);
	PRINT((p - (char *)(st)));

//7
	const char *p = "12345";
	const char **q = &p;
	*q = "abcde";
	const char *s = ++p;
	p = "XYZWVU";
	printf("%c\n", *++s);

// 6
	int a = 1, b;
	for (b = 1; b <= 10; b++) {
		if (a >= 8)
			break;
		if (a % 2 == 1) {
			a += 3;
			continue;
		}
		a -= 3;
	}
	PRINT(b);

//5
	long l;
	scanf("%ld", &l);

//4
	int a;
	int *p;
	p = &a;
	*p = 0x500;
	a = (int)(*(&p));              
	if (a == (int)p)                   // a == (int)p;  正确
		printf("equal!\n");
	else
		printf("not equal!\n");
	a = (int)(&(*p));
	if (a == (int)p)
		printf("equal!\n");
	else
		printf("not equal!\n");


//3
	int m = 5;
	if (m++ > 5)
		printf("%d\n", m);
	else
		printf("%d\n", m++); // 传值调用， m 先用后加，先把m 的值传给printf，后加，即 传 6 



//2
	int a = 1, b = 2, m = 2, n = 2;
	int ret;
	ret = (m = a > b) && ++n;
	PRINT(n);


//12
	struct A{
		short i;
		short j;
		char * ptr;
		long array[100];
		char b[4];
		char *c;
	};
#define PRINT_ME (char *)&(((struct A *)0)->c)
	printf("%d\n", PRINT_ME);



// 13
	int arr[] = {6, 7, 8, 9, 10};
	int *ptr = arr;
	*(ptr++) += 123;      //等价于   *(ptr) = *(ptr) + 123; ptr = ptr + 1;
	PRINT(*++ptr);
	PRINT(*ptr++);


//18
	char str[] = "morning";
	abc(str);
	puts(str);

#endif


//19
	char a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	short *p = (short *)(a + 2);
	short i = *p;
	printf("%x\n", i);


	return 0;
}
