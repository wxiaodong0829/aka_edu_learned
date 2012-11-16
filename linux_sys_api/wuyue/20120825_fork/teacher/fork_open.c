#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd; pid_t pid;

    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    pid = fork();
    if(pid == 0){
        write(fd, "hello ", 6);			/*父子进程共享打开的文件*/
    }else{
        sleep(1);
        write(fd, "world", 5);
    }

    return 0;
}
