#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include "err.h"

#define SERV_PORT 60000
#define SERV_IP "127.0.0.1"

#define MAX_EXP 2    /* 长工 个数 */

sem_t empty, full, avail;
volatile int cfd;

void *pth(void * args)
{
	int sfd;
	char buf[BUFSIZ];
	int exp_left, n, j;

	while (1) {
		printf("%u waiting\n", (unsigned)pthread_self());/* 报告自己在粮仓门口等着呢 */
		sem_wait(&full);
		sfd = cfd;
		sem_post(&empty);

		printf("%u working\n", (unsigned)pthread_self());/* 报告自己将要去工作 */
		while ((n = read(sfd, buf, BUFSIZ)) != 0) {
			for (j = 0; j < n; j++)
				buf[j] = toupper(buf[j]);
			write(sfd, buf, n);
		}
		close(sfd);

		sem_getvalue(&avail, &exp_left);
		if (exp_left >= MAX_EXP)
			break;
			sem_post(&avail);
	}

	printf("%u exit\n", (unsigned)pthread_self());		/* 感慨一句，我要走了...   而且不带走一片云彩*/
	return NULL;
}

int main(void)
{
	pthread_t tid;
	int i, n;
	struct sockaddr_in socket_serv, socket_chld;
	int lfd, sfd;


	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1)
		error_sys("socket");

	memset(&socket_serv, 0, sizeof(socket_serv));
	memset(&socket_chld, 0, sizeof(socket_serv));
	socket_serv.sin_family = AF_INET;
	socket_serv.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &socket_serv.sin_addr.s_addr);
	
	n = bind(lfd, (struct sockaddr *)&socket_serv, sizeof(socket_serv));
	if (n == -1)
		error_sys("bind");

	for (i = 0; i < MAX_EXP; i++) {
		n = pthread_create(&tid, NULL, pth, NULL);
		if (n != 0)
			perror("pthread_create");
		pthread_detach(tid);
	}

	n = listen(lfd, 20);
	if (n == -1)
		error_sys("listen");

	sem_init(&empty, 0, 1);
	sem_init(&full , 0, 0);
	sem_init(&avail, 0, MAX_EXP);

	while (1) {
		n = sizeof(socket_chld);
		sfd = accept(lfd, (struct sockaddr *)&socket_chld, &n);
//		if (sfd == -1)//待封装
		
		sem_wait(&empty);
		cfd = sfd;
		sem_post(&full);

		n = sem_trywait(&avail);
		if (n == -1) {
			if (errno == EAGAIN) {
				n = pthread_create(&tid, NULL, pth, NULL);
				if (n != 0)
					perror("pthread_create");
				pthread_detach(tid);
			} else {
				perror("sem_trywait");
				return -1;
			}
		}
	}

	close(lfd);
	printf("should not be here...\n");

	return 0;
}
