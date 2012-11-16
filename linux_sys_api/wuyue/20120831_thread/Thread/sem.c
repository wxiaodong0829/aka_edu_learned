#include <pthread.h>
typedef struct
{
    int num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}my_sem_t;

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
    while(sem->num <= 0)
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
