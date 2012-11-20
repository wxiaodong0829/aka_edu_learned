/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月15日 13时19分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define SERV_IP "192.168.204.104"
#define SERV_PORT 8000

int main(int argc, char *argv[])
{
	int sfd, cfd, fd, n;
	struct sockaddr_in servaddr;
	char buf[1024], path[1024], *filename, *ip, buf2[10];
	
	if(strchr(argv[1], ':') != NULL)
		n = 1;
	else  
		n = 2;
	ip = strtok(argv[n], ":");
	filename = strtok(NULL, ":");

	sfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, ip, &servaddr.sin_addr);

	connect(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(n == 1){
		sprintf(path, "%s%s", "do", filename);
		filename = rindex(filename, '/');
		write(sfd, path, strlen(path));
		read(sfd, buf, 10);
		sprintf(buf, "%s%s", argv[2], filename);

		fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("open success ....\n");
		while((n = read(sfd, buf, 1024)))
			write(fd, buf, n);
		close(fd);
	}
	if(n == 2){
		sprintf(path, "%s%s/%s", "up", filename, argv[1]);
		
		write(sfd, path, strlen(path));

		fd = open(argv[1], O_RDONLY);
		while((n = read(fd, buf, 1024)))
			write(sfd, buf, n);
		close(fd);
	}
	close(sfd);

	return 0; 
}
