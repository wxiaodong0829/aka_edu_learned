/*************************************************************************
    > File Name: stack.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月10日 星期五 10时44分28秒
 ************************************************************************/
#include "stack.h"
#define STACK_BUF 512


static mytype_t stack[STACK_BUF];
static int top = -1;

void push(mytype_t c)
{
	stack[++top] = c;
}
mytype_t pop(void)
{
	return stack[top--];
}
int is_empty(void)
{
	return top == -1;
}

