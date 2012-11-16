#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ROOT "./cli"

#define CONN 1             /* 链接的状态  链接   下载   搞定 */
#define READ 2
#define DONE 3

struct myfile
{
	char *filename;
	int fd;
	int cfd;
	int status;
};

/* ./app file1 file2 file3 ... */
int main(int argc, char *argv[])
{
	int sfd, fd;
	struct sockaddr_in serv_addr;
	int n, i, flags;
	int res, max_fd, nread, nleft;
	struct myfile *list;
	fd_set wset, rset, wtmp, rtmp;

	n = argc - 1;
	list = (struct myfile *)malloc(sizeof(struct myfile) * n);
	for(i = 0; i < n; i++){
		list[i].filename = argv[i + 1];
		list[i].fd = -1;
		list[i].cfd = -1;
		list[i].status = 0;
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	FD_ZERO(&wset); FD_ZERO(&rset);
	max_fd = -1;

	for(i = 0; i < n; i++){
		sfd = socket(AF_INET, SOCK_STREAM, 0);
		list[i].cfd = sfd;
		if(sfd > max_fd)
			max_fd = sfd;

		flags = fcntl(sfd, F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(sfd, F_SETFL, flags);
		
		res = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(res == -1){
			if(errno != EINPROGRESS){
				perror("connect error");
				return -1;
			}
			list[i].status = CONN;
			FD_SET(sfd, &rset);
			FD_SET(sfd, &wset);
		}else if(res == 0){
			char path[1024];
			
			list[i].status = READ;

			flags = fcntl(sfd, F_GETFL);
			flags &= ~O_NONBLOCK;
			fcntl(sfd, F_SETFL, flags);
			
			FD_SET(sfd, &rset);
			write(sfd, list[i].filename, strlen(list[i].filename));
			
			sprintf(path, "%s/%s", ROOT, list[i].filename);
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			list[i].fd = fd;
		}
	}

	nleft = n;
	while(nleft > 0){
		wtmp = wset, rtmp = rset;
		select(max_fd + 1, &rtmp, &wtmp, NULL, NULL);

		for(i = 0; i < n; i++){
			if(list[i].status == DONE)
				continue;
			if(list[i].status == CONN){
				if(FD_ISSET(list[i].cfd, &wtmp)){
					if(FD_ISSET(list[i].cfd, &rtmp)){
						printf("connect error...\n");
						return -1;
					}else{
						char path[1024];
			
						list[i].status = READ;

						flags = fcntl(list[i].cfd, F_GETFL);
						flags &= ~O_NONBLOCK;
						fcntl(list[i].cfd, F_SETFL, flags);
			
						FD_CLR(list[i].cfd, &wset);
						write(list[i].cfd, list[i].filename, strlen(list[i].filename));
			
						sprintf(path, "%s/%s", ROOT, list[i].filename);
						fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						list[i].fd = fd;
					}
				}
			}else if(list[i].status == READ){
				char buf[1024];
				
				if(FD_ISSET(list[i].cfd, &rtmp)){
					nread = read(list[i].cfd, buf, 1024);
					if(nread == 0){
						close(list[i].cfd);
						close(list[i].fd);
						FD_CLR(list[i].cfd, &rset);
						list[i].status = DONE;
						printf("%s done...\n", list[i].filename);
						nleft--;
					}else
						write(list[i].fd, buf, nread);
				}
			}
		}

		printf("one round is over...\n");
	}

	return 0;
}
