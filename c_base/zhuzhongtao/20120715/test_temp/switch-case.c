/*************************************************************************
    > File Name: switch-case.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 18时01分01秒
 ************************************************************************/

#include<stdio.h>

int main(int argc, char *argv[])
{
	int a, b;
	char c;


	printf("please input(num1 + num2):");
	scanf("%d %c %d", &a, &c, &b);
	switch(c)
	{
		case '+':
			printf("%d %c %d = %d\n", a, c, b, a + b);
			break;
		case '-':
			printf("%d %c %d = %d\n", a, c, b, a - b);
			break;
		case'*':
			printf("%d %c %d = %d\n", a, c, b, a * b);
			break;
		case '/':
			printf("%d %c %d = %d\n", a, c, b, a % b);
			break;
		default:
			printf("lnvalid input!\n");
			break;
	}

	return 0;
}
