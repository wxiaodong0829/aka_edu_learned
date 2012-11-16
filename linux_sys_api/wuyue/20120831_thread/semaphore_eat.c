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
sem_t chop[NUM];
sem_t place;
#if 0
void *philosopy(void *arg)
{
	char name[NUM] = {'A', 'B', 'C', 'D', 'E'};
	int l, r;	
	int i = (int)arg;
	if (i == 0)
		l = NUM - 1;
	else
		l = i - 1;
	r = i;
	while (1) {
		sem_wait(&place);
		usleep(rand() % 10);
		sem_wait(&chop[l]);
		printf("Philosopher %c fetches chopstick %d\n", name[i], l + 1);
		sem_wait(&chop[r]);
		printf("Philosopher %c fetches chopstick %d\n", name[i], r + 1);
		usleep(rand() % 10);
		sem_post(&chop[l]);
		sem_post(&chop[r]);
		sem_post(&place);
		printf("Philosopher %c releases chopstick %d %d\n", name[i], l + 1, r + 1);
	}

	return NULL;
}
#endif
void *philosopy(void *arg)
{
	char name[NUM] = {'A', 'B', 'C', 'D', 'E'};
	int l, r;	
	int i = (int)arg;
	if (i == 0)
		l = NUM - 1;
	else
		l = i - 1;
	r = i;
//	while (1) {
		sem_wait(&place);
		usleep(rand() % 10);
		sem_trywait(&chop[l]);
		printf("Philosopher %c fetches chopstick %d\n", name[i], l + 1);
		sem_trywait(&chop[r]);
		printf("Philosopher %c fetches chopstick %d\n", name[i], r + 1);
		usleep(rand() % 10);
		sem_post(&chop[l]);
		sem_post(&chop[r]);
		sem_post(&place);
		printf("Philosopher %c releases chopstick %d %d\n", name[i], l + 1, r + 1);
//	}

	return NULL;
}
int main(int argc, char *argv[])
{
	pthread_t pid[NUM];
	int i, n;

	sem_init(&place, 0, NUM - 2);
	for (i = 0; i < NUM; i++)
		sem_init(&chop[i], 0, 1);
	for (i = 0; i < NUM; i++) {
		n = pthread_create(&pid[i], NULL, philosopy, (void *)i);
		if (n != 0)
			perror("pthread_create");
	}
	for (i = 0; i < NUM; i++) {
		pthread_join(pid[i], NULL);
	}
	for (i = 0; i < NUM; i++) {
		sem_destroy(&chop[i]);
	}
	sem_destroy(&place);
	
	return 0;
}
