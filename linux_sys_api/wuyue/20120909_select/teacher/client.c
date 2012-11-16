#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//#define SERV_IP "192.168.204.112"
#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

int main(void)
{
	int sfd, n;
	struct sockaddr_in serv_addr;
	char buf[1024];

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);	

	n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	while(1){
		n = read(STDIN_FILENO, buf, 1024);
		if(n == 0)
			break;
		write(sfd, buf, n);
		n = read(sfd, buf, 1024);
		write(STDOUT_FILENO, buf, n);
	}

	close(sfd);

	return 0;
}
