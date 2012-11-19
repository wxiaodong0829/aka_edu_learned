/*************************************************************************
    > File Name: pthread_mutex.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月31日 星期五 10时21分53秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thr_fn(void *arg)
{

	while (1) {
		pthread_mutex_lock(&mutex);
		printf("hello ");
		sleep(rand() % 5);
		printf("world\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 5);
	}

	return NULL;
}
int main(void)
{
	pthread_t tid;
	pthread_create(&tid, NULL, thr_fn, NULL);

	while (1) {
		pthread_mutex_lock(&mutex);
		printf("HELLO ");
		sleep(rand() % 5);//模拟长时间操作 共享资源 的情况
		printf("WORLD\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 5);
	}
	pthread_mutex_destroy(&mutex);

	return 0;
}
