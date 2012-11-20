#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define ROOT "."

void err_sys(const char *str)
{
    perror("str");
    exit(-1);
}
int main(int argc, char *argv[])
{
    int status, i;
    int cflags = REG_EXTENDED;
    int cfd, n, fd;
    struct sockaddr_in serv_addr;
    char buf[1024], path[1024], dest[1024];
    char *p, *q;
    // regmatch_t pmatch[1];
    //size_t nmatch = 1;
    //regex_t reg;
    //const char *pattern = "([01]?|2[0-4]|25[0-5])\.([01]?|2[0-4]|25[0-5])\.([01]?|2[0-4]|25[0-5])\.([01]?|2[0-4]|25[0-5]))";

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1)
        err_sys("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

    connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // regcomp(&reg, pattern, cflags);
    //regexec(&reg, p, nmatch, pmatch, 0)
    if(argv[1][3] == '.'){
        strcpy(dest, argv[1]);
        write(cfd, dest, strlen(dest));
        p = rindex(argv[1], '/');
        p = p + 1;
        sprintf(path, "%s/%s", ROOT, p);
        read(cfd, buf, 2);
        if(buf[0] == '0'){
            printf("no such file\n");
            exit(1);
        }else if(buf[0] == '1'){
            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            while(1){
                n = read(cfd, buf, 1024);
                if(n == 0)
                    return 0;
                else
                    write(fd, buf, n);
            }
        }
    }else if(argv[1][0] == '.'){
        strcpy(dest, argv[1]);
        write(cfd, dest, strlen(dest));
        fd = open(dest, O_RDONLY);
        if(fd == -1)
            err_sys("open fail");
        while(1){
            n = read(fd, buf, 1024);
            if(n == 0)
                break;
            else
                write(cfd, buf, n);
        }
    }else{
        sprintf(dest, "%s/%s", ROOT, argv[1]);
        p = strstr(argv[1], "/");
        p += 1;
        q = strstr(argv[2], ":");
        q += 1;
        sprintf(path, "%s%s", q, p);
        write(cfd, path, strlen(path));
        fd = open(dest, O_RDONLY);
        if(fd == -1)
            err_sys("open fail");
        while(1){
            n = read(fd, buf, 1024);
            if(n == 0)
                break;
            else
                write(cfd, buf, n);
        }
    }
    
    close(fd);
    close(cfd);
    return 0;
}
