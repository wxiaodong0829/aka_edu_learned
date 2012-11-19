/*************************************************************************
    > File Name: condition_variable.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月31日 星期五 15时06分42秒
 ************************************************************************/
/* 条件变量 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct msg {
	struct msg *next;
	int num;
};

struct msg *head;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * consumer(void *p)
{
	struct msg *mp;
	for (;;) {
		pthread_mutex_lock(&lock);
		while (head == NULL) {
			pthread_cond_wait(&has_product, &lock);
		}
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock);
		printf("Consume %d\n", mp->num);
		free(mp);
		sleep(rand() % 5);
	}
}
void *producer(void *p)
{
	struct msg *mp;
	for (;;) {
		mp = malloc(sizeof(struct msg));
		pthread_mutex_lock(&lock);
		mp->next = head;
		mp->num = rand() % 1000;
		head = mp;
		printf("Produce %d\n", mp->num);
		pthread_mutex_unlock(&lock);
		sleep(rand() % 5);
	}
}
int main(int argc, char **argv)
{
	pthread_t pid, cid;

	srand(time(NULL));
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	
	return 0;
}
