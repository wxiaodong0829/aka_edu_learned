/*************************************************************************
    > File Name: pthread_exit_join.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月30日 星期四 14时59分34秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int a; int b;
}res_t;
void *thr_fn (void *arg)
{
	res_t *p;

	p = malloc(sizeof(*p));
	p->a = 100, p->b = 200;

	return (void *)p;
}
int main(int argc, char **argv)
{
	pthread_t tid;
	res_t *q;
	
	pthread_create(&tid, NULL, thr_fn, NULL); 

	pthread_join(tid, (void **)&q); // waitpid(); 等待指定进程结束，此函数是等待指定线程结束，并获取结束状态存放的地址.
	printf("%d, %d\n", q->a, q->b);

	return 0;
}
