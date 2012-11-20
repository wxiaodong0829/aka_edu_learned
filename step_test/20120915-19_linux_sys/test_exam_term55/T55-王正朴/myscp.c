#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define N 512
#define SERV_PORT 7000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc ,char *argv[])
{
	if(argc != 3)
		err_sys("thr argument is wrong");

	struct sockaddr_in servaddr;
	struct stat st;
	int cfd,n,i,j = 0,fd;
	char *q,*p,*begin, *token[N],*filename;
	char path[N],buf[N],despath[N],cur_p[N],tmp_filename[N],save_path[N];

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd == -1)
		err_sys("socket failed");

#if 0
	n =stat(filename, &st);
	if(n == -1)
		err_sys("stat failed");
#endif


	//p = argv[1];
	//n =stat(p, &st);
	//if(n == -1)
	//	err_sys("stat failed");

	p = argv[1];
	q = strstr(p, ":");
	if(q != NULL)
	{
		//	if(p[j] == ':' && S_ISREG(st.st_mode))
		for(i = 0,begin = p; token[i] = strtok(begin , ":"); begin = NULL,i++)
			;
		strcpy(path, token[i - 1]);
		printf("%s %s\n",path,token[0]);
		filename = rindex(path, '/');
		filename++;
		sprintf(tmp_filename,"%c%s",'d',filename);
		puts(filename);

		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, token[0], &servaddr.sin_addr.s_addr);

		n = connect(cfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
		if (n == -1)
			err_sys("connect failed");


		write(cfd, tmp_filename, strlen(tmp_filename));

		sprintf(despath,"%s/%s", argv[2], filename );

		fd = open(despath, O_WRONLY |O_CREAT |O_TRUNC ,0644);
		if(fd == -1)
			err_sys("despath open failed");

		while(n = read(cfd, buf, 1024))
		{
			write(fd, buf, n);
		}
		printf("finish loading ...\n");
		close(cfd);
		close(fd);
	}

	else
	{
		strcpy(cur_p, argv[1]);
		filename = rindex(cur_p, '/');
		filename++;
		//sprintf(tmp_filename, "%c%s", 'u',filename);
		for(i = 0, begin = argv[2];token[i] = strtok(begin , ":"); begin = NULL, i++)
			;

		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, token[0], &servaddr.sin_addr.s_addr);

		n = connect(cfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
		if(n == -1)
			err_sys("connect failed");

		fd = open(cur_p, O_RDONLY);
		if(fd == -1)
			err_sys("open failed");
		sprintf(tmp_filename, "%c%s/%s", 'u',token[i -1],filename);
		
		write(cfd, tmp_filename, strlen(tmp_filename));

	//	strcpy(save_path, token[i - 1]);
	//	write(cfd, save_path, strlen(save_path));
		n =read(cfd, buf, 1024);
		buf[n] = '\0';
		if((strcmp(buf ,"upload")) == 0)
		{

		while(n = read(fd, buf, 1024))
			write(cfd, buf, n);
		printf("file transmit over...\n");
		close(fd);
		}
	}

	return 0;
}

