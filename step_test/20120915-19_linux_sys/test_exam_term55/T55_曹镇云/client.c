#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>

void err_sys(const char *str)
{
    perror(str);
    exit(-1);
}
void err_usr(const char *str)
{
    perror(str);
    exit(-1);
}

char *only_filename(char *str) /*delete the pathname, just file name left*/
{
    char *p;
    p = rindex(str, '/');
    strcpy(str, p + 1);

    return str;
}
#if 0
char *only_dirname(char *str)/*delete the IP, just directory name left*/
{
    char *p;
    p = index(str, ':');
    strcpy(str, p + 1);
    return str;
}
#endif
int main(int argc, char *argv[])
{
    int sfd, fd;
    int n, m;
    char path[1024];
    char buf[1024];
    char tranbuf[2048];
    struct sockaddr_in serv_addr;

    if(argc != 3)
        err_usr("client input error");

    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1)
        err_sys("client socket error");
    n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(n == -1)
        err_sys("client connect error");

    char *tmp;
    char filename[1024];
    tmp = strstr(argv[1], ":");/*find the IP*/
    if(tmp != NULL)     
    {   /* download ./myscp 127.0.0.1:/home/pub/file1 . */
        sprintf(tranbuf, "%s@%s", argv[1], argv[2]);
        write(sfd, tranbuf, strlen(tranbuf));
        strcpy(filename, only_filename(tmp));
        sprintf(path, "%s/%s", argv[2], filename);
        fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);    
        if(fd == -1)
            err_sys("client open error");
        while(n = read(sfd, buf, 1024))
            write(fd, buf, n);
        printf("success....\n");

        close(fd);
    }
    else 
    {   /* send to server ./myscp ./dir1/file2 127.0.0.1:. */
        /* send to server ./myscp ./dir1/file2 127.0.0.1:/home/pub/ */
        char dir[1024];
        strcpy(dir, argv[1]);
        strcpy(filename, only_filename(argv[1]));        
        sprintf(tranbuf, "%s@%s", filename, argv[2]);
        write(sfd, tranbuf, strlen(tranbuf));

        fd = open(dir, O_RDONLY);
        printf("success....\n");
        if(fd == -1)
            err_sys("client open error");
        while(n = read(fd, buf, 1024))
            write(sfd, buf, n);

        close(fd);
    }

    close(sfd);
    return 0;
}
