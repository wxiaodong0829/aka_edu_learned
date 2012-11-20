#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void err_sys(const char *str)
{
    perror(str);
    exit(-1);
}
char *only_dirname(char *str)
{
    char *p;
    p = index(str, ':');
    strcpy(str, p + 1);
    return str;
}
char *only_filename(char *str)
{
    char *p;
    p = rindex(str, '/');
    strcpy(str, p + 1);
    return str;
}
int main(void)
{
    int lfd, cfd;
    int n;
    struct sockaddr_in serv_addr;

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
        err_sys("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

    n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(n == -1)
        err_sys("server bind error");
    listen(lfd, 20);
    if(n == -1)
        err_sys("server listen error");

    while(1){
        cfd = accept(lfd, NULL, NULL);
        if(cfd == -1)
            err_sys("server accept error");

        char buf[2048], path[1024];
        char argv1[1024], argv2[1024];
        char *ptmp;
        int fd;

        n = read(cfd, buf, 1024);
        buf[n] = '\0';

        ptmp = strtok(buf, "@");
        strcpy(argv1, ptmp); /*argv[1]*/
        ptmp = strtok(NULL, "@");
        strcpy(argv2, ptmp);/*argv[2]*/

        char *tmp;
        
        char openf[1024];
        strcpy(openf,argv1);

        tmp = strstr(argv1, ":");
        if(tmp != NULL)
        { /* download file to client directory*/
            char filename[1024];
            strcpy(filename, only_filename(tmp));
            printf("the flie : \n%s download success...\n", filename);

            tmp = strstr(openf, ":");
            sprintf(path, ".%s", tmp + 1);
            printf("%s\n", path);
            fd = open(path, O_RDONLY);
            if(fd == -1)
                err_sys("server open error");
            while(n = read(fd, buf, 1024))
                write(cfd, buf, n);

            close(fd);
            close(cfd);
        }
        else
        { /*send file to server directory*/
            if((tmp = strstr(argv2, "/")) == NULL)
            {
               // printf("the flie : \n%s download success...\n", filename);
                printf("client download %s success...\n", argv1);
                sprintf(path, "%s/%s", "./", argv1);

                fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if(fd == -1)
                    err_sys("server open error");
                while(n = read(cfd, buf, 1024)) 
                    write(fd, buf, n);
                close(fd);
                close(cfd);
            }
            else
            {
                char dir_name[1024];
                strcpy(dir_name, only_dirname(argv2));
                printf("server:%s send to cilent success...\n", argv1);
                sprintf(path, ".%s/%s", dir_name, argv1);
                printf("%s\n", path);

                fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if(fd == -1)
                    err_sys("server open error");
                while(n = read(cfd, buf, 1024)) 
                    write(fd, buf, n);
                close(fd);
                close(cfd);
            }
        }
    }

    close(lfd);
    printf("server should not be here.....");
    return 0;
}
