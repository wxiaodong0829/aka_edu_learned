/*************************************************************************
    > File Name: err.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月03日 星期五 09时11分56秒
 ************************************************************************/

#include <stdio.h>

void test3(void)
{	
	int *a;
	int p;
	int b;
	a = 0x804a050;
	p = 0x804a050;
	b = 0x804a050;
	printf("test3 &a = 0x%x\n", (int)&a);
}

void test2(void)
{	
	int *p;
	printf("p = 0x%x\n", (int)p);
	printf("test2 &p = 0x%x\n", (int)&p);
	*p = 100;
	printf("test2 ok\n");
}

void test(void)
{	
	int *p;
	int a[2];
	printf("1\n");
	//*p = 100;
	printf("test ok\n");
//	test3();
	printf("&a = 0x%x\n", (int)&a);
	printf("&a[-10] = 0x%x\n", (int)&a[-10]);
	a[-10] = 0x804a050;
	test2();
}


int main(void)
{
#if 0
	int *p = NULL;
	p = *(main + 10);
	*p = 1;
	printf("%d\n", *p);
#endif 
#if 0
	int *p = (int *)0x804a050;
	printf("1\n");
	*p = (int)100;
	printf("2\n");
	return 0;
#endif 
	test();
	return 0;
}
