#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/* exec 共享打开的文件*/

int main(void)
{
    int fd; pid_t pid;
    char *myargv[] = {"date", NULL};

    while(1){
        pid = fork();
        if(pid == 0){
            fd = open("time.log", O_WRONLY | O_CREAT | O_APPEND, 0644); /* 不能放while上面，若如此，则使此文件管理结构struct file中的引用计数器会被多个子进程修改，使得写进文件的内容不能每隔一秒就返回，因当系统隐式回收资源，或内核缓存区4K满时，才更新到文件中，不能每隔一秒更新一次，当效率和功能冲突时，必须选功能*/
            dup2(fd, STDOUT_FILENO);

            execvp("date", myargv);
            printf("should not be here...\n");
        }else
            sleep(1);
    }

    return 0;
}
