/*************************************************************************
    > File Name: creat_n_pthread.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月30日 星期四 11时44分55秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thr_fn (void *arg)
{
	int i = (int)arg;

	if(i == 3)
		pthread_exit(NULL);
	sleep(i);
	printf("I'm %dth thread\n", i);//	printf("I'm %dth thread", (int)arg);// 终端是行缓冲机制，所以只有等终端文件描述符为0时才一起输出。
	return NULL;
}
int main(int argc, char **argv)
{
	pthread_t tid;
	int i, n = 5;
	
	if (argc > 1)
		n = atoi(argv[1]);
	for (i = 0; i < n; i++) 
		tid = pthread_create(&tid, NULL, thr_fn, (int *)i); //若传 (void *)&i, 则这么多线程均可共享此地址中的数据，不安全，其它线程可更改

	sleep(i); //
	printf("I'm parent\n");

	return 0;
}
