/*
 * =====================================================================================
 *
 *       Filename:  10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月04日 17时33分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
int add(int a, int b)
{
	return a+b;
}
int sub(int a, int b)
{
	return a-b;
}
int cheng(int a, int b)
{
	return a*b;
}
int chu(int a, int b)
{
	return a/b;
}
int main()
{
	int a, b;
	char n;
	printf("+-*/\n");
	scanf("%c %d %d", &n, &a, &b);
	switch(n)
	{
	case '+':printf("%d\n", add(a, b));break;
	case '-':printf("%d\n", sub(a, b));break;
	case '*':printf("%d\n",cheng(a, b));break;
	case '/':printf("%d\n",chu(a, b));break;
	case '#':break;
	}
	return 0;

}
