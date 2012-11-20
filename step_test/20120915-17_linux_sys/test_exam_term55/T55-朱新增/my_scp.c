#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <regex.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(-1);
}
int is_regex(char *arg)
{
	char *pattern = SERV_IP;
	char ebuf[128];
	regex_t reg;
	int z;
	regmatch_t pm[1];
	const size_t nmatch = 1;
	z = regcomp(&reg, pattern, 0);
	if(z != 0)
	{
		regerror(z, &reg, ebuf, sizeof(ebuf));
		fprintf(stderr, "%s: pattern '%s'\n", ebuf, pattern);
		return 1;
	}
	z = regexec(&reg, arg, nmatch, pm, 0);	
	if(z != 0)
	{
		regerror(z, &reg, ebuf, sizeof(ebuf));
		fprintf(stderr, "%s: regcom('%s')\n", ebuf, arg);
		return 1;
	}
	regfree(&reg);
	return 0;
}
int main(int argc, char *argv[])
{
	int sfd, fd;
	struct sockaddr_in serv_addr;
	int n, i;
	char buf[1024], path[255], filename[255];
	char *token, *begin, *p, *q;

	q = strstr(argv[1], ":");
	if(q == NULL)
	{
		q = strstr(argv[2], ":");
		n = (int)(q - argv[2]);
		strncpy(buf, argv[2], n);
		buf[n] = '\0';
		n = is_regex(buf);
		if(n != 0)
		{
			printf("IP ERROR\n");
			exit(0);
		}
	}
	else
	{
		n = (int)(q - argv[1]);
		strncpy(buf, argv[1], n);
		buf[n] = '\0';
		n = is_regex(buf);
		if(n != 0)
		{
			printf("IP ERROR\n");
			exit(0);
		}

	}


	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);


	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		err_sys("socket error");
	n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("connect error");
	p = strstr(argv[1], ":");
	if(p == NULL)
	{
		printf("client 要上传文件\n");
		p = strstr(argv[2], ":");
		*p = 'S';
		strcpy(path, p);
		n = strlen(path);
		if(path[n-1] == '/')
			path[n-1]='\0';
		strcpy(buf, argv[1]);
		for(begin=buf;(token= strtok(begin, "/")); begin = NULL)
			strcpy(filename, token);
		sprintf(path, "%s/%s",path, filename);
		printf("%s\n", path);
		write(sfd, path, strlen(path));
		fd = open(argv[1], O_RDONLY);
		if(fd == -1)
			err_sys("open error");
		while(n = read(fd, buf, 1024))
			write(sfd, buf, n);
		close(fd);
		close(sfd);

	}
	else
	{
		printf("client 要下载文件\n");
		*p = 'L';
		strcpy(path, p);
		write(sfd, path, strlen(path));
		for(begin=argv[1];(token= strtok(begin, "/")); begin = NULL)
			strcpy(filename, token);
		n = strlen(argv[2]);
		if(argv[2][n-1] == '/')
			argv[2][n-1] = '\0';
		sprintf(path, "%s/%s",argv[2], filename);
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while(n = read(sfd, buf, 1024))
			write(fd, buf, n);
		close(fd);
		close(sfd);

	}
	return 0;
}
