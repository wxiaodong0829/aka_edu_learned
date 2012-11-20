#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define N 1024
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}
void err_usr(const char *str)
{
	perror(str);
	exit(2);
}
int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	int sockfd, n;
	char buf[N], *parg1, *parg2, *ip;
	char tmp[5]; //存放是下载文件还是上传文件
	socklen_t servaddr_len;
	struct stat stbuf1, stbuf2;

	if (argc != 3) {
		printf("./myscp [127.0.0.1:/home/test3/pub/file1] .");
		err_usr("wrong command");
	}
	
	parg1 = strstr(argv[1], ":");
	if (parg1 != NULL) {
		parg1[0] = '\0';
		parg1 = parg1 + 1;
		ip = argv[1];
		stat(parg1, &stbuf1);
		strcpy(tmp, "down");
	} else {
		parg1= argv[1];
		stat(parg1, &stbuf1);
	}
	parg2 = strstr(argv[2], ":");
	if (parg2 != NULL) {
		parg2[0] = '\0';
		parg2 = parg2 + 1;
		ip = argv[2];
		stat(parg2, &stbuf1);
		strcpy(tmp, "up");
	} else  {
		parg2 = argv[2];
		stat(parg2, &stbuf2);
	}
#if 0
	//printf("%s, %s, %s, %s\n", tmp, parg1, parg2, ip);
	if (S_ISREG(stbuf1.st_mode))
		//printf("argv[1] is regular file\n");
		printf("argv[1]:%s is regular file\n", parg1);
	else 
		printf("argv[1]:%s isnot regular file\n", parg1);
	if (S_ISDIR(stbuf2.st_mode))
		printf("argv[2]:%s is dir file\n", parg2);
	else 
		printf("argv[2]:%s isnot directory file\n", parg2);
	//if (S_ISREG(stbuf1.st_mode) && S_ISDIR(stbuf2.st_mode))
	//	printf("argv[1] is regular file and argv[2] is dir file\n");
	//else 
	//	err_usr("argv[1] isn't regular file or argv[2] isn't directory file\n");
	//return 0;
#endif
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, ip, &servaddr.sin_addr.s_addr);

	if (strcmp(tmp, "down") == 0) { /* down */
		char path[N];
		int fd, flen;
		char *p;
		int len = 0;
		p = rindex(parg1, '/');
		sprintf(path, "%s/%s", parg2, p+1);
		fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			err_sys("open error");
		sprintf(buf, "%s %s", tmp, parg1);
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
#if 0
		n = recvfrom(sockfd, buf, 4, 0, NULL, NULL);
		if (strncmp(buf, "fail", 4) == 0) {
			printf("no such file or directory");
			exit(2);
		}
#endif
		n = recvfrom(sockfd, &flen, 4, 0, NULL, NULL);
		lseek(fd, flen-1, SEEK_CUR);
		write(fd, "a", 1);
		lseek(fd, -flen, SEEK_CUR);
		while (1) {
			n = recvfrom(sockfd, buf, N, 0, NULL, NULL);
			if (n == -1) {
				printf("fail to down...\n");
				err_sys("recvfrom error");
			}
			write(fd, buf, n);
			len += n;
			if (len == flen) {
				printf("success down!!!\n");
				return 0;
			}
		}
	} else {/* up */ 
		char path[N];
		int fd, flen;
		char *p;
		sprintf(path, "%s", parg1);
		fd = open(path, O_RDONLY);
		if (fd == -1)
			err_sys("open error");
		flen = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		p = rindex(argv[1], '/');
		sprintf(path, "%s/%s", parg2, p+1);
		sprintf(buf, "%s %s %d", tmp, path, flen);
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		while (n = read(fd, buf, N)) {
			sendto(sockfd, buf, n, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		}	
		n = recvfrom(sockfd, buf, N, 0, NULL, NULL);
		buf[n] = '\0';
		if (n == -1)
			err_sys("recvfrom error");
		if (strcmp(buf, "OK")) {
			printf("fail to up...\n");
			exit(1);
		} else {
			printf("success up!!!\n");
			return 0;
		}
		close(fd);
	}
	return 0;
}
