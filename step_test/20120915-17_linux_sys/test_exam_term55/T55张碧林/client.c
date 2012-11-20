#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define SERV_PORT 8000
#define MAXLEN 1204

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int fsize(char *name)
{
    struct stat stbuf;
    if(stat(name, &stbuf) == -1)
        err_sys("cannot access %s\n");
    if((stbuf.st_mode & S_IFMT) == S_IFREG)
        return 0;
    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        return 1;
    else 
        return -1;
}

int main(int argc, char *argv[])
{
	int sfd, n, fd, size;
	struct sockaddr_in serv_addr;
    socklen_t ser_len;
	char buf[MAXLEN], *token1, *token2;
    char *SERV_IP, *op, path[32], *p, *q;

    if(argc != 3)
    {
        printf("input error\nyou should input ./client arg arg\n");
        return 0;
    }

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);


    //no.1  下载文件
    if((q = strstr(argv[1], ":")) != NULL)
    {
        int re_size = 0;
        
        op = "DOWN";

        token1 = strtok(argv[1], ":"); 
        token2 = strtok(NULL, ":");
        if(fsize(token2) != 0)
        {
            printf("argv[1]:should be a regular file\n"); 
            return -1;
        }
        if(fsize(argv[2]) != 1)
        {
            printf("argv[2]:should be a dirent file\n"); 
            return -1;
        }
        SERV_IP = token1;
	    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

        n = sendto(sfd, op, strlen(op), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(n == -1)
            err_sys("send error");
        n = sendto(sfd, token2, strlen(token2), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(n == -1)
            err_sys("send error");
        p = rindex(token2, '/');
        sprintf(path, "%s/%s", argv[2], p+1);
        fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
        if(fd == -1)
            err_sys("open error");

        recvfrom(sfd, &size, 4, 0, NULL, 0);
        lseek(fd, size-1, SEEK_CUR);
        write(fd, "a", 1);
        lseek(fd, -size, SEEK_CUR);
        while(1)
        {
            n = recvfrom(sfd, buf, MAXLEN, 0, NULL, 0);
            if(n == -1)
                err_sys("recvfrom error");
            write(fd, buf, n);
            re_size += n;
            if(re_size == size)
                break;
        }
        close(fd);
    }
    //no.1  end

    //no.2          /*上传文件*/
    else if((q = strstr(argv[2], ":")) != NULL)
    { 
        token1 = strtok(argv[2], ":"); 
        token2 = strtok(NULL, ":");
        if(fsize(argv[1]) != 0)
        {
            printf("argv[1]:should be a dirent file\n"); 
            return -1;
        }
        if(fsize(token2) != 0)
        {
            printf("argv[1]:should be a regular file\n"); 
            return -1;
        }
        SERV_IP = token1;
	    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

        op = "UP"; 

        fd = open(argv[1], O_RDONLY);
        if(fd == -1)
            err_sys("open error");
        size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        n = sendto(sfd, op, strlen(op), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(n == -1)
            err_sys("send error");

        p = strstr(argv[1], "/");
        if(p == NULL)
            sprintf(path, "%s/%s", token2, argv[1]);
        else
        {
            p = rindex(argv[1], '/');
            sprintf(path, "%s/%s", token2, p+1);
        }
        n = sendto(sfd, path, strlen(path), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(n == -1)
            err_sys("send error");
        n = sendto(sfd, &size, 4, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(n == -1)
            err_sys("send error");
        while(n = read(fd, buf, 1024))
        {
            if(n == -1)
                err_sys("read error");
            sendto(sfd, buf, n, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        }
        close(fd);
    }
    //no.2  end
    else
    {
        printf("error input\n"); 
        return 0;
    }
    close(sfd);

	return 0;
}
