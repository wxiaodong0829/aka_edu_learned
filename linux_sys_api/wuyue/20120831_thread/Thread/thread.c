#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *tfn(void *arg)
{
    int i;

    i = (int)arg;
    if(i == 2)
        pthread_exit(NULL);
    sleep(i);
    printf("%dth, pid : %d, tid : %u\n",
        i + 1, getpid(), (unsigned)pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    int n = 5, i;
    pthread_t tid;

    if(argc == 2)
        n = atoi(argv[1]);
    for(i = 0; i < n; i++)
        pthread_create(&tid, NULL, tfn, (void *)i);
    //sleep(n);
    printf("i'm the main...\n");

    return 0;
}
