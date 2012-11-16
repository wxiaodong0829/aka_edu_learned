#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

void *smalloc(size_t size)
{
    char *p;
    p = (char *)mmap(NULL, size, 
        PROT_READ | PROT_WRITE, 
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0);
    if(p == MAP_FAILED)
        p = NULL;
    return p;
}
void sfree(void *ptr, size_t size)
{
    munmap(ptr, size);
}

int main(void)
{
    pid_t pid;
    int *p; 

    p = (int *)smalloc(sizeof(int));
    *p = 100;

    pid = fork();
    if(pid == 0){
        *p = 200;
    }else{
        sleep(1);
        printf("*p : %d\n", *p);
    }

    sfree(p, sizeof(int));

    return 0;
}   
