#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if(pid == 0)
        return 0;
    else
        while(1);

    return 0;
}
