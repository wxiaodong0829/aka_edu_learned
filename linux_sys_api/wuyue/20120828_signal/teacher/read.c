#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

void myhandler(int singo)
{
    printf("catch sigint...\n");
}

int main(void)
{
    int n;
    char buf[1024];
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = myhandler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGINT, &act, NULL);

    n = read(STDIN_FILENO, buf, 1024);
    if(n == -1){
        if(errno == EINTR)
            printf("sys_call interrupted by signal...\n");
        else
            perror("error");
    }else
        write(STDOUT_FILENO, buf, n);

    return 0;
}
