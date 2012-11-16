#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

void err_sys(const char *str)
{
    perror(str);
    exit(1);
}
int main(void)
{
    int ifd, n, size;
    char buf[1024];
    struct inotify_event *p;

    ifd = inotify_init();
    if(ifd == -1)
        err_sys("inotify_init error");
    n = inotify_add_watch(ifd, ".", IN_CREATE);
    if(n == -1)
        err_sys("inotify_add_watch error");
    while(1){
        n = read(ifd, buf, 1024);
        size = 0; p = (struct inotify_event *)buf;
        while(size < n){
            if(p->mask & IN_CREATE){
                if(p->len > 0)
                    printf("%s create\n", p->name);
            }else
                printf("other...\n");
            size = size + sizeof(struct inotify_event) 
                + p->len;
            p = (struct inotify_event *)(buf + size);
        }
    }

    close(ifd);

    return 0;
}
