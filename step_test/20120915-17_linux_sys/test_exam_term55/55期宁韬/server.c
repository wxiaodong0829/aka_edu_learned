#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define ROOT "."
void err_sys(const char *str)
{
    perror("str");
    exit(1);
}

void sig_chld(int signo)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(void)
{
    struct sockaddr_in serv_addr;
    struct sigaction act;
    int lfd, cfd;
    int n, fd, i;
    char buf[1024], path[1024];
    char *p, *q;

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
        err_sys("socket error");
    memset(&act, 0, sizeof(act));
    act.sa_handler = sig_chld;
    act.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

    n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(n == -1)
        err_sys("bind error");

    n = listen(lfd, 20);
    if(n == -1)
        err_sys("listen error");

    while(1){
        cfd = accept(lfd, NULL, NULL);
        n = read(cfd, buf, 1024);
        buf[n] = '\0';

        if(strncmp(buf, "192", 3) == 0){
            p = strstr(buf, ":");     
            p = p + 1;
            sprintf(path, "%s", p);
            fd = open(path, O_RDONLY);
            if(fd == -1){
                write(cfd, "0", 2);
                close(cfd);
                return 0;
            }else{
                write(cfd, "1", 2);
                while(1){
                    n = read(fd, buf, 1024);
                    if(n == 0)
                        break;
                    else
                        write(cfd, buf, n);
                }
            }
        }else if(buf[0] == '.'){
            p = rindex(buf, '/');
            p += 1;
            sprintf(path, "%s/%s", ROOT, p);
            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd == -1)
                err_sys("open error");

            while(1){
                n = read(cfd, buf, 1024);
                if(n == 0)
                    break;
                else
                    write(fd, buf, n);
            }
        }else{
            fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd == -1)
                err_sys("open error");
            while(1){
                n = read(cfd, buf, 1024);
                if(n == 0)
                    break;
                else 
                    write(fd, buf, n);
            }
        }
        close(fd);
        close(cfd);
    }

    return 0;
}
