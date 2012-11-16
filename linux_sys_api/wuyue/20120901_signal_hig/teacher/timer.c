#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>

void my_handler(int signo, siginfo_t *info, void *context)
{
    char *p;    
    p = (char *)info->si_value.sival_ptr;
    printf("%s", p);
}

int main(void)
{
    struct sigaction act;
    timer_t timer_id;
    struct sigevent evp;
    char buf[1024];
    struct itimerspec it = {{1,0}, {1,0}};

    memset(&act, 0, sizeof(act));
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = my_handler;
    sigaction(SIGALRM, &act, NULL);

    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_signo = SIGALRM;
    evp.sigev_value.sival_ptr = (void *)buf;

    timer_create(CLOCK_REALTIME, &evp, &timer_id);
    timer_settime(timer_id, 0, &it, NULL);

    while(1);

    return 0;
}
