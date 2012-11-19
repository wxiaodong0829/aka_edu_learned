/*************************************************************************
    > File Name: my_semaphore_by_cond_var.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月31日 星期五 15时38分47秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
typedef struct {
	int num;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}my_sem_t;

#define NUM 5
int queue[NUM];
my_sem_t blank_number, product_number;


int my_sem_init(my_sem_t *sem, int pshared, int value)
{
	sem->num = value;
	pthread_mutex_init(&sem->mutex, NULL);
	pthread_cond_init(&sem->cond, NULL);

	return 0;
}
int my_sem_destroy(my_sem_t *sem)
{
	sem->num = -1;
	pthread_mutex_destroy(&sem->mutex);
	pthread_cond_destroy(&sem->cond);
	return 0;
}
int my_sem_wait(my_sem_t *sem)
{
	pthread_mutex_lock(&sem->mutex);
	while (sem->num <= 0)
		pthread_cond_wait(&sem->cond, &sem->mutex);
	sem->num--;
	pthread_mutex_unlock(&sem->mutex);
	return 0;
}
int my_sem_post(my_sem_t *sem)
{
	pthread_mutex_lock(&sem->mutex);
	sem->num++;
	pthread_mutex_unlock(&sem->mutex);
	pthread_cond_broadcast(&sem->cond);
	return 0;
}

void *producer(void *arg)
{
	static int p = 0;
	while(1) {
		my_sem_wait(&blank_number);
		queue[p] = rand() % 1000;
		printf("produce %d\n", queue[p]);
		p = (p + 1) % NUM;
		sleep(rand() % 5);
		my_sem_post(&product_number);
	}
}
void *consumer(void *arg)
{
	static int c = 0;
	while (1) {
		my_sem_wait(&product_number);
		printf("Consume %d\n", queue[c]);
		c = (c + 1) % NUM;
		sleep(rand() % 5);
		my_sem_post(&blank_number);
	}
}
int main(int argc, char *argv[])
{
	pthread_t pid, cid;
	int n;
	my_sem_init(&blank_number, 0, NUM);
	my_sem_init(&product_number, 0, 0);
	n = pthread_create(&pid, NULL, producer, NULL);
	if (n != 0)
		perror("pthread_create");
	n = pthread_create(&cid, NULL, consumer, NULL);
	if (n != 0)
		perror("pthread_create");
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	my_sem_destroy(&blank_number);
	my_sem_destroy(&product_number);

	return 0;
}
