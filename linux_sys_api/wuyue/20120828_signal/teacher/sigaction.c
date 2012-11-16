#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

int flag = 0;
void my_handler(int signo)
{ 
    flag = 1; 
}
int main(void)
{
    struct sigaction act;
    int i;
    memset(&act, 0, sizeof(act));
    act.sa_handler = my_handler;
    sigaction(SIGALRM, &act, NULL);
    alarm(1);
    for(i = 0; !flag; i++);
    printf("i : %d\n", i);

    return 0;
}
