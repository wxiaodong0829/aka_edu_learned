#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

#define N 1024

int main(int argc, char *argv[])
{


  if(argc < 3)
  {
	printf("error\n");	
	exit(-1);
  }


  int sfd, fd, n;
  struct sockaddr_in serv_addr;

  sfd = socket(AF_INET, SOCK_STREAM, 0);


  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

  connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));


  while(1)
  {
	char buf[N],  path[N];
	char *p;

	if(strstr(argv[1], ":"))
    	{
	  sprintf(path, "%s", argv[1]);
	  write(sfd, path, strlen(path) + 1);
	  p = rindex(argv[1], '/');
	  sprintf(path, "%s/%s", argv[2], p + 1);

	  fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	  while((n = read(sfd, buf, N)) != 0)
		write(fd, buf, n);
	  break;	
	}

	else 
	 {
	  sprintf(path, "%s %s", argv[1], argv[2]);
	  write(sfd, path, strlen(path) + 1);
	  fd = open(argv[1], O_RDONLY);


	  while((n = read(fd, buf, N)) != 0)
		write(sfd, buf, n);
	  break;	
	}
  }

  close(fd);
  close(sfd);

  return 0;
}
