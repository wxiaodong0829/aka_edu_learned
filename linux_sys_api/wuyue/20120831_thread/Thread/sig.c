#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

sigset_t set;

void sig_int(int signo)
{
    printf("%u catch sigint...\n", 
        (unsigned)pthread_self());
}

void *tfn(void *arg)
{
    int i = (int)arg;

#if 0
    if(i != 2)
        pthread_sigmask(SIG_BLOCK, &set, NULL);
#endif

    while(1)
        pause();
    return NULL;
}

#define NUM 5

int main(void)
{
    struct sigaction act;
    pthread_t tid[NUM]; int i;
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    memset(&act, 0, sizeof(act));
    act.sa_handler = sig_int;
    sigaction(SIGINT, &act, NULL);

    for(i = 0; i < NUM; i++){
        pthread_create(&tid[i], NULL, tfn, (void *)i);
        printf("%dth %u create...\n", 
            i + 1, (unsigned)tid[i]);
    }
    printf("the main %u\n", (unsigned)pthread_self());
    //pthread_sigmask(SIG_BLOCK, &set, NULL);

    pthread_kill(tid[2], SIGINT);

    for(i = 0; i < NUM; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
