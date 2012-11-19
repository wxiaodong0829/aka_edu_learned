#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/mman.h>

#define SERV_PORT 8000
#define SERV_IP "127.0.0.1"

int main(int argc, char *argv[])
{
	char *usr_name;
	int sfd, n, i;
	struct sockaddr_in serv_addr;
	char buf[1024];
	pid_t *pid, tpid;

	usr_name = argv[1];

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		return -1;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	sprintf(buf, "syn %s", usr_name);
	n = sendto(sfd, buf, strlen(buf), 0,
		(struct sockaddr *)&serv_addr, sizeof(serv_addr));
	n = recvfrom(sfd, buf, 1024, 0, NULL, NULL);
	buf[n] = '\0';
	if(strcmp(buf, "OK")){
		printf("fail to login...\n");
		return 0;
	}

	pid = (pid_t *)mmap(NULL, sizeof(pid) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

	for(i = 0; i < 2; i++){
		if((tpid = fork()) == 0)
			break;
		pid[i] = tpid;
	}
	if(i == 0){
		while(1){
			n = read(STDIN_FILENO, buf, 1024);
			if(buf[0] == '#')
				break;
			n = sendto(sfd, buf, n, 0,
				(struct sockaddr *)&serv_addr, 
				sizeof(serv_addr));
		}
		
		kill(pid[1], SIGUSR1);

		return 0;
	}else if(i == 1){
			while(1){
				n = recvfrom(sfd, buf, 1024, 0, NULL, NULL);
				write(STDOUT_FILENO, buf, n);
			}
			
			return 0;
	}else
		for(i = 0; i < 2; i++)
			wait(NULL);

tryagain:
	sprintf(buf, "fin %s", usr_name);
	n = sendto(sfd, buf, strlen(buf), 0,
		(struct sockaddr *)&serv_addr, sizeof(serv_addr));
	n = recvfrom(sfd, buf, 1024, 0, NULL, NULL);
	buf[n] = '\0';
	if(strcmp(buf, "OK")){
		sleep(1);
		printf("fail to logout...\n");
		goto tryagain;
	}

	close(sfd);
	
	return 0;
}
