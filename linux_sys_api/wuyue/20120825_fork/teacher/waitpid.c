#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int n;

    pid = fork();
    if(pid == 0){
        while(1);
    }else{
        //wait(NULL);
        n = waitpid(pid, NULL, WNOHANG);
    }

    return 0;
}
