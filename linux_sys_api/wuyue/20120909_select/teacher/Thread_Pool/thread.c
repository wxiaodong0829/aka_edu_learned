#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 2

sem_t empty, full, avail;
volatile int cfd;

void *tfn(void *arg)
{
	int sfd, n, i;
	char buf[1024];
	int val;

	while(1){
		printf("%u waiting\n", (unsigned)pthread_self());
		
		sem_wait(&full);
		sfd = cfd;
		sem_post(&empty);

		printf("%u working\n", (unsigned)pthread_self());
		while(1){
			n = read(sfd, buf, 1024);
			if(n == 0)
				break;
			for(i = 0; i < n; i++)
				buf[i] = toupper(buf[i]);
			write(sfd, buf, n);
		}
		close(sfd);

		sem_getvalue(&avail, &val);
		if(val >= MAX)
			break;
		sem_post(&avail);
	}

	printf("%u exit\n", (unsigned)pthread_self());

	return 0;
}

int main(void)
{
	int lfd, sfd, i, n;
	struct sockaddr_in serv_addr;
	pthread_t tid;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	listen(lfd, 20);

	sem_init(&empty, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&avail, 0, MAX);

	for(i = 0; i < MAX; i++){
		pthread_create(&tid, NULL, tfn, NULL);
		pthread_detach(tid);
		printf("%u show-up\n", (unsigned)tid);
	}
		
	while(1){
		sfd = accept(lfd, NULL, NULL);
		
		sem_wait(&empty);
		cfd = sfd;
		sem_post(&full);

		n = sem_trywait(&avail);
		if(n == -1){
			if(errno == EAGAIN){
				pthread_create(&tid, NULL, tfn, NULL);
				pthread_detach(tid);
				printf("%u new worker\n", (unsigned)tid);
			}else{
				printf("error...\n");
				return -1;
			}
		}
	}

	return 0;
}
