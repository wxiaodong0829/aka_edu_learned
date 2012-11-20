#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

#define N 1024

int main(void)
{
		int lfd, cfd; 
		int n;
		struct sockaddr_in serv_addr;
		char buf[N];

		lfd = socket(AF_INET, SOCK_STREAM, 0);

		bzero(&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

		n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		n = listen(lfd, 15);

		while(1){
				char path[N];
			    char *p, *q; 
				char *filename, *pathname;
				int fd;
				cfd = accept(lfd, NULL, NULL);
				n = read(cfd, buf, N);
				buf[n] = '\0';
				q = buf;

				if((p = strstr(buf, " ")) != NULL) {
						*p = '\0';
						filename =rindex(q, '/');
						pathname = strstr(p + 1, ":");
						sprintf(path, "%s/%s", pathname + 1, filename + 1);

						fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

						while ((n = read(cfd, buf, N)) != 0)
								write(fd, buf, n);

						close(fd);
						close(cfd);
				}	
				else{
						pathname = strstr(buf, ":");
						sprintf(path, "%s", pathname + 1);


						fd = open(path, O_RDONLY);

						while((n = read(fd, buf, N)) != 0)
								write(cfd, buf, n);

						close(fd);
						close(cfd);
				}

		}

		return 0;
}
