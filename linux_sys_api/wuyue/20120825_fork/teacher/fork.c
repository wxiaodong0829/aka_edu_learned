#include <stdio.h>
#include <unistd.h>

#define NUM 5

/* ./app [n] */
int main(int argc, char *argv[])
{
    int n = NUM;
    int i; pid_t pid;

    if(argc == 2)
        n = atoi(argv[1]);
    for(i = 0; i < n; i++)
        if((pid = fork()) == 0)
            break;
    if(i == n){ /* parent */
        sleep(n);
        printf("i'm parent\n");
    }else{ /* child */
        sleep(i);
        printf("i'm %dth child\n", i + 1);
    }

    return 0;
}
