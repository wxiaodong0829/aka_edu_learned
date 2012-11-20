#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>
#include <fcntl.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

#define N 1024

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}
void err_usr(const char *str)
{
	fputs(str,stderr);
	exit(2);
}
int is_have_m(char m, const char * buf, int len)
{
	int i;
	for(i = 0; i < len; i++)
	{
		if(buf[i] == m)
			return i;
	}
	return -1;
}
int sock_init(int lfd, struct sockaddr_in serv_addr, char *ip)
{
	int n;

	lfd = socket(AF_INET, SOCK_STREAM, 0);

	if(lfd == -1)
		err_sys("socker error in sock_init");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

	n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");

	n = listen(lfd, 20);
	if(n == -1)
		err_sys("listen error");

	return lfd;
}
int argv_analy(int cfd, char *path)
{
	int len, pos_con, pos_ip, pos_file = 0;
	char *download_file, buf[N], *upload_file, *file;
	int fp, n;

	len = strlen(path);

	pos_con = is_have_m('-', path, len);
	if(pos_con == -1)/*不含'-'*/
		err_sys("is_have_m('-') error");

	pos_ip = is_have_m(':', path, len);
	if(pos_ip == -1)
		err_sys("is_have_m(':') error");

	if(pos_ip < pos_con){/*download, need to write*/

		int len_downfile;

		if(strncmp(path,SERV_IP, strlen(SERV_IP))!=0)
			err_usr("ip wrong");

		len_downfile = pos_con - pos_ip;
		download_file = malloc(sizeof(char) * len_downfile);
		strncpy(download_file, &path[pos_ip + 1], len_downfile - 1);
		printf("download_file : %s\n",download_file);
		printf("start download...\n");

		fp = open(download_file, O_RDONLY);
		if(fp == -1)
			err_sys("open file error");

		while((n = read(fp, buf, N)) != 0)
			write(cfd, buf, n);
		printf("download finish...\n");

		close(fp);
		free(download_file);

	}else if(pos_ip > pos_con){/*upload, need to read*/

		int len_upfile;

		if(strncmp(&path[pos_con + 1],SERV_IP, strlen(SERV_IP))!=0)
			err_usr("ip wrong");

		len_upfile = pos_con;
		upload_file = malloc(sizeof(char) * (len_upfile + 1));
		strncpy(upload_file, path, len_upfile);
		upload_file[len_upfile] = '\0';
		printf("upload_file : %s\n",upload_file);

		while((pos_file = is_have_m('/', upload_file, len_upfile)) != -1){
			len_upfile = strlen(upload_file);
			strncpy(upload_file, &upload_file[pos_file + 1], len_upfile - pos_file - 1);
			upload_file[len_upfile - pos_file -1] = '\0';
		}

		file = malloc((len_upfile + strlen(&path[pos_ip + 1]) + 1) * sizeof(char));
		bzero(file, len_upfile + strlen(&path[pos_ip + 1]) + 1);

		if(path[pos_ip + 1] != '.')
		sprintf(file,"%s%c%s", &path[pos_ip + 1], path[len - 1] == '/' ? ' ':'/', upload_file);
		else
			sprintf(file, "./%s",upload_file);

		printf("start upload...\n");
		fp = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fp == -1){
			printf("open file error in argv_analy\n");
			return -1;
		}

		while((n = read(cfd, buf, N))!= 0)
			write(fp, buf, n);

		printf("upload finish...\n");
		close(fp);
		free(upload_file);
		free(file);
	}
	return cfd;
}
int main(void)
{
	int lfd = 0, n, cfd;
	struct sockaddr_in serv_addr;
	char buf[N];
	char path[N];

	lfd = sock_init(lfd, serv_addr, SERV_IP);
	while(1){
		cfd = accept(lfd, NULL, NULL);
		if(cfd == -1)
			err_sys("accept error");
		printf("start connect..\n");
		n = read(cfd, buf, N);
		strncpy(path, buf, n);
		argv_analy(cfd, path);
		close(cfd);
		printf("wait connect....\n");
	}
	return 0;
}
