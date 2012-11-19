#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/inotify.h>
#include <signal.h>
#include <dirent.h>
#include <sys/mman.h>
#include "err.h"

pid_t *sp;

int disp_dir(const char *dir_name)
{
    int i; DIR *dp;
    struct dirent *p;

    dp = opendir(dir_name);
    if(dp == NULL)
        return -1;
    i = 0;
    while(p = readdir(dp)){
        if(p->d_name[0] != '.'){
            printf("%s", p->d_name);
            if(i == 4){
                printf("\n");
                i = 0;
            }else{
                printf(" ");
                i++;
            }
        }
    }
    printf("\n");

    closedir(dp);

    return 0;
}

void sig_usr1(int signo)
{
    /* do nothing... */
}

int watch_dir(const char *dir_name)
{
    int ifd; int wd, n;
    char buf[1024]; int size;
    struct inotify_event *p;

    ifd = inotify_init();
    wd = inotify_add_watch(ifd, dir_name, IN_CREATE);
 
    while(1){   
        n = read(ifd, buf, 1024);
        size = 0; p = (struct inotify_event *)buf;
        while(size < n){
            if(p->mask & IN_CREATE){
                kill(sp[0], SIGUSR1);
            }
            size += sizeof(struct inotify_event) 
                + p->len;
            p = (struct inotify_event *)&buf[size];
        }
    }

    close(ifd);

    return 0;
}

int main(void)
{
    int i;
    pid_t pid;
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = sig_usr1;
    sigaction(SIGUSR1, &act, NULL); 

    sp = (pid_t *)mmap(NULL, sizeof(pid_t) * 2,
        PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,
        -1, 0);
    for(i = 0; i < 2; i++){
        if((pid = fork()) == 0)
            break;
        sp[i] = pid;
    }
    if(i == 0){ /* 1st child */
        while(1){
            disp_dir(".");
            pause();
        }
    }else if(i == 1){ /* 2nd child */
        watch_dir(".");
    }else{ /* parent */
        for(i = 0; i < 2; i++)
            wait(NULL);
    }

    return 0;
}
