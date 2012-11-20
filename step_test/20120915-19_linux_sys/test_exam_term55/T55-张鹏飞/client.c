#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define SERV_PORT 8000
#define SERV_IP "127.0.0.1"

void err_sys(const char *str)
{
	perror(str);
	exit(-1);
}
int main (int argc, char *argv[])
{
	int lfd, fd, n;
	struct sockaddr_in serv_addr;
	struct stat buf_t;
	char buf[1024], path[1024];
	char *p, *q;

	if(argc != 3)
		err_sys("argc error");

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		err_sys("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	connect(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	p = strstr(argv[1], ":");
	if(p == NULL)
	{
		p = argv[1];
		n = stat(p, &buf_t);
		if(n == -1)
			err_sys("stat error");
		if(S_ISREG(buf_t.st_mode))
		{
			q = strstr(argv[2], ":");
			if(q != NULL)
			{
				q++;
				n = stat(q, &buf_t);
				if(n == -1)
					err_sys("stat error");
				if(S_ISDIR(buf_t.st_mode))
				{
					strcpy(buf, q);
					write(lfd, buf, sizeof(buf));
					
					fd = open(p, O_RDONLY);
					p = rindex(p, '/');
					p++;
					strcpy(buf, p);
					write(lfd, buf, sizeof(buf));

					while(n = read(fd, buf, 1024))
						write(lfd, buf, n);

					close(fd);
					close(lfd);
					return 0;			
				}

				else
				{
					printf("input wrong argc\n");
					close (lfd);
					return 0;
				}
			}
			else
			{
					printf("input wrong argc\n");
					close (lfd);
					return 0;

			}

		}		

	}
	else
	{
		p++;
		n = stat(p, &buf_t);
		if(n == -1)
			err_sys("stat error");
		if(S_ISREG(buf_t.st_mode))
		{
			q = strstr(argv[2], ":");
			if(q == NULL)
			{
				q = argv[2];
				n = stat(q, &buf_t);
				if(n == -1)
					err_sys("stat error");
				if(S_ISDIR(buf_t.st_mode))
				{
					strcpy(buf, p);
					p = rindex(p, '/');
					p++;
					sprintf(path, "%s/%s", q, p);

					write(lfd, buf, strlen(buf));
					fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					while(n = read(lfd, buf, 1024))
						write(fd, buf, n);
					close(fd);
					close(lfd);
					return 0;
				}
				else
				{
					printf("input error argc\n");
					close(lfd);
					exit(-1);
				}
		}

	}
	}
	printf("should not be here\n");
	return 0;	
}
