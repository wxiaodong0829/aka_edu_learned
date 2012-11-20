#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
		perror(str);
		exit(1);
}
int main(int argc, char *argv[])
{
		int sfd, fd, n;
		struct sockaddr_in serv_addr;

		if(argc != 3)
		{
				perror("input error");
				exit(1);
		}

		sfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sfd == -1)
				err_sys("socket error");

		bzero(&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

		n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if (n == -1) 
				if (errno != EINPROGRESS)
						err_sys("connect error");

		while(1)
		{
				char buf[1024],  path[1024], *p;
				struct stat src;

				if(strstr(argv[1], ":"))/*download*/
				{
						sprintf(path, "%s", argv[1]);
						write(sfd, path, strlen(path) + 1);
						p = rindex(argv[1], '/');

						sprintf(path, "%s/%s", argv[2], p + 1);


						fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
						if (fd == -1)
								err_sys("open error");
						while(n = read(sfd, buf, 1024))
								write(fd, buf, n);

						break;
				}
				else /*upload*/
				{
						sprintf(path, "%s %s", argv[1], argv[2]);
						write(sfd, path, strlen(path) + 1);

						fd = open(argv[1], O_RDONLY);
						if (fd == -1)
								err_sys("open error");

						while(n = read(fd, buf, 1024))
								write(sfd, buf, n);

						break;
				}
}

close(fd);
close(sfd);

return 0;
}
