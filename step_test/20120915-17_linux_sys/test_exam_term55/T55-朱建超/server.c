/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月15日 12时49分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define SERV_IP "192.168.204.124"
#define SERV_PORT 8000
#define ROOT "."

int main(void)
{
	int sfd, cfd;
	struct sockaddr_in servaddr;


	sfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr.s_addr);

	bind(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(sfd, 5);

	while(1){
			int n, fd;
			char buf[1024], path[1024], *p, temp[1024];

			cfd = accept(sfd, NULL, NULL);
			close(sfd);
		//	memset(temp, 0, strlen(temp));

			n = read(cfd, buf, 1024);
			buf[n] = '\0';
			p = buf;
			p += 2;
			sprintf(path, "%s%s", ROOT, p);
			printf("%s\n", buf);

		if(buf[0] == 'd' && buf[1] == 'o'){   /* download */
			fd = open(path, O_RDONLY);
			while(n = read(fd, temp, 1024))
				write(cfd, temp, n);
			printf("download over....\n");
			close(fd);
		}
		if(buf[0] == 'u' && buf[1] == 'p'){  /* upload */
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while(n = read(cfd, temp, 1024))
				write(fd, temp, n);
			printf("upload over....\n");
			close(fd);
		}
		close(cfd);
		printf("close  cfd...\n");
	}

	return 0;
}
