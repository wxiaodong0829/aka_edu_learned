#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
	int lfd, n;
	struct sockaddr_in serv_addr;
	char buf[1024];

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	connect(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	while(1){
		n = read(0, buf, 1024);
		if(n == 0)
			break;
		write(lfd, buf, n);
		n = read(lfd, buf, 1024);
		write(1, buf, n);
	}

	return 0;
}
