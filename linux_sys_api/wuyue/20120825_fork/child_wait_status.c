#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void pr_exit(int status)
{
    if(WIFEXITED(status)){
        printf("child exit normally, eixt no : %u\n", WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
        printf("child killed by signal, signo : %d\n", WTERMSIG(status));
    }else
        printf("other...\n");
}

int main(void)
{
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0)
        return 100;
    wait(&status);
    pr_exit(status);

    pid = fork();
    if(pid == 0){
        char *p = NULL;
        *p = 'H';
        return 0;
    }
    wait(&status);
    pr_exit(status);

    pid = fork();
    if(pid == 0){
        int a = 100 / 0;
        printf("a : %d\n", a);
        return 0;
    }
    wait(&status);
    pr_exit(status);

    return 0;
}
