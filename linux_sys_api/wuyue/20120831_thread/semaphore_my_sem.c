/*************************************************************************
    > File Name: semaphore.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月31日 星期五 13时25分30秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM 5
int queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg)
{
	static int p = 0;
	while(1) {
		sem_wait(&blank_number);
		queue[p] = rand() % 1000;
		printf("produce %d\n", queue[p]);
		p = (p + 1) % NUM;
		sleep(rand() % 5);
		sem_post(&product_number);
	}
}
void *consumer(void *arg)
{
	static int c = 0;
	while (1) {
		sem_wait(&product_number);
		printf("Consume %d\n", queue[c]);
		c = (c + 1) % NUM;
		sleep(rand() % 5);
		sem_post(&blank_number);
	}
}
int main(int argc, char *argv[])
{
	pthread_t pid, cid;
	sem_init(&blank_number, 0, NUM);
	sem_init(&product_number, 0, 0);
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	sem_destroy(&blank_number);
	sem_destroy(&product_number);

	return 0;
}
