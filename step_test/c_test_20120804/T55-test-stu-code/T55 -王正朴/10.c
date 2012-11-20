#include <stdio.h>
#include <stdlib.h>


typedef int(*result) (void *,void *);

int add(void *a ,void *b)
{
	int ta =*(int *)a;
	int tb =*(int *)b;
	return ta + tb;
}
int sub(void *a ,void *b)
{
	int ta =*(int *)a;
	int tb =*(int *)b;
	return ta - tb;
}
int mul(void *a ,void *b)
{
	int ta =*(int *)a;
	int tb =*(int *)b;
	return ta * tb;
}
int dive(void *a ,void *b)
{
	int ta =*(int *)a;
	int tb =*(int *)b;
	return (int) (ta/tb) ;
}
int main()
{
	int a ,b ;
	char ch;
	result add;
	result sub;
	result mul;
	result dive;
	printf("enter the a ,b and character:\n");
	scanf("%d %d %c",&a,&b, &ch);
	switch(ch)
	{
	case '+':   add((void *)a, (void *)b); break;
	case '-':   sub((void *)a, (void *)b); break;
	case '*':   mul((void *)a, (void *)b); break;
	case '/':   dive((void *)a, (void *)b); break;
	case '#':   exit(1); break;
	}
	return 0;
}
