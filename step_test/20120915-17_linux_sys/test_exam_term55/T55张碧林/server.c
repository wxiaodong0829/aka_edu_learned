#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

#define MAXLEN 1204
#define LEN 64
#define OPLEN 8

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int sfd;
	struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
	char buf[MAXLEN], path[LEN], op[OPLEN];
	int n, fd, size, re_size = 0;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");

	while(1)
    {

        cli_len = sizeof(cli_addr);	
        n = recvfrom(sfd, op, OPLEN, MSG_WAITALL, (struct sockaddr *)&cli_addr, &cli_len);
        op[n] = '\0';
        if(n == -1)
            err_sys("recvfrom error");

        if(strcmp(op, "DOWN") == 0) /*  下载文件 */
        {
            n = recvfrom(sfd, path, LEN, MSG_WAITALL, (struct sockaddr *)&cli_addr, &cli_len);
            if(n == -1)
                err_sys("recvfrom error");

            path[n] = '\0';
            fd = open(path, O_RDONLY);
            if(fd == -1)
                err_sys("open error");

            size = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, SEEK_SET);
            sendto(sfd, &size, 4, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
            while(n = read(fd, buf, 1024))
            {
                if(n == -1)
                    err_sys("read error");
                n = sendto(sfd, buf, n, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr)); 
                if(n == -1)
                    err_sys("sendto error");
            }
            close(fd);
        }
        else if(strcmp(op, "UP") == 0) /* 上传文件*/ 
        {
            n = recvfrom(sfd, path, LEN, 0, NULL, 0);                    
            path[n] = '\0';
            if(n == -1)
                err_sys("recvfrom error");
            n = recvfrom(sfd, &size, 4, 0, NULL, 0);                    
            if(n == -1)
                err_sys("recvfrom error");
            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
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
    }

	return 0;
}
