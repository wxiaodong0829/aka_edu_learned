#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define N 1024
#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}
int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int sockfd;
	char buf[N];
	int i, n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
		err_sys("socket error");

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr.s_addr);

	n = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));	
	if (n == -1)
		err_sys("bind error");

	printf("Accepting connection...\n");
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		n = recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
		buf[n] = '\0';
		if (strncmp(buf, "down", 4) == 0) {/* down */
			char *path;
			int  fd;
			int flen;
			path = strstr(buf, " ");
			fd = open(path+1, O_RDONLY);
			if (fd ==-1) {
				//sendto(sockfd, "fail", 4, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
				err_sys("open error");
			}
			flen = lseek(fd, 0, SEEK_END);
			lseek(fd, 0, SEEK_SET);
			n = sendto(sockfd, &flen, 4, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
			while (n = read(fd, buf, 1024)) {
				sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
			}
			close(fd);
		}
		if (strncmp(buf, "up", 2) == 0) {/* up */
			char *path, *count;
			int fd;
			int flen;
			int len = 0;
			path = strstr(buf, " ");
			count = strstr(path + 1, " ");
			count[0] = '\0';

			fd = open(path+1, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				err_sys("open error");
			flen = atoi(count + 1);
			lseek(fd, flen-1, SEEK_CUR);
			write(fd, "a", 1);
			lseek(fd, -flen, SEEK_CUR);

			while (1) {
				n = recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
				if (n == -1) {
					printf("fail to up...\n");
					err_sys("recvfrom error");
				}
				write(fd, buf, n);
				len += n;
				if (len == flen) {
					sendto(sockfd, "OK", 2, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
					break;
				}
			}
			close(fd);
		}
		printf("round one time\n");
	}
	return 0;	
}
