#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *tfn(void *arg)
{
    while(1){
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
    pthread_create(&tid, NULL, tfn, NULL);
    while(1){
        pthread_mutex_lock(&mutex);
        printf("HELLO ");
        sleep(rand() % 5);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 5);
    }

    return 0;
}

