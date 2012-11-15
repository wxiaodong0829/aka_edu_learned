/*************************************************************************
    > File Name: fifo.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月10日 星期五 16时35分06秒
 ************************************************************************/

#include <stdio.h>

typedef int mytype_t;

mytype_t queue[BUFSIZ];
int head = -1;
int tail = -1;

void enqueue(mytype_t n)
{
	queue[++tail] = n;
}
mytype_t dequeue(void)
{
	return queue[++head];
}
int is_empty(void)
{
	return head == tail;
}

int main(void)
{
	int n;
	while(1) {
		scanf("%d", &n);
		if (n == -1)
			break;
		enqueue(n);
	}
	while(is_empty() == 0) {
		printf("%4d", dequeue());
	}
	printf("\n");
	return 0;
}
