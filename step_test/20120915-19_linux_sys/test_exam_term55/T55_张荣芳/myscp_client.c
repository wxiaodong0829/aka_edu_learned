#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <dirent.h>

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

	n = connect(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("connect error in sock_init");

	return lfd;
}
int argv_analy(int cfd, char *path)
{
	int len, pos_con, pos_ip, fp, n, pos_file;
	int sum = 0;
	char buf[N];
	char *down_file, *up_file;

	len = strlen(path);
	pos_con = is_have_m('-', path, len);
	if(pos_con == -1)/*不含'-'*/
		err_sys("is_have_m('-') error");

	pos_ip = is_have_m(':', path, len);

	if(pos_ip == -1)/*have no ':'*/
		err_sys("is_have_m(':') error");

	if(pos_ip < pos_con){/*download, need to read*/
		int len_downfile;

		if(strncmp(path,SERV_IP, strlen(SERV_IP))!=0)
			err_usr("ip wrong");

		len_downfile = pos_con - pos_ip;
		down_file = malloc(sizeof(char)*len_downfile);
		strncpy(down_file, &path[pos_ip + 1], len_downfile - 1);
		printf("down_file : %s\n", down_file);

		while((pos_file = is_have_m('/', down_file, strlen(down_file))) != -1){
			strncpy(down_file, &down_file[pos_file + 1], strlen(down_file) - pos_file - 1);
			down_file[strlen(down_file) - pos_file -1] = '\0';
		}

		printf("start down....\n");
		fp = open(down_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fp == -1)
			err_sys("open file error");

		while((n = read(cfd, buf, N)) != 0){
			write(fp, buf, n);
			sum = sum + n;
		}

		printf("downfile finish....\n");
		printf("total : %d\n", sum);
		close(fp);
		free(down_file);

	}else if(pos_ip > pos_con){/*upload, need to write*/

		if(strncmp(&path[pos_con + 1],SERV_IP, strlen(SERV_IP))!=0)
			err_usr("ip wrong");

		up_file = malloc(sizeof(char)*(pos_con + 1));
		strncpy(up_file, path, pos_con);
		up_file[pos_con] = '\0';
		printf("upload_file : %s\n",up_file);

		printf("start upload...\n");
		fp = open(up_file, O_RDONLY);
		if(fp == -1)
			err_sys("open file error");

		while((n = read(fp, buf, N))!= 0){
			write(cfd, buf, n);
			sum = sum + n;
		}
		printf("upload finish...\n");
		printf("total : %d\n", sum);

		close(fp);
		free(up_file);
	}

	return cfd;
}

/*./myscp IP:/home/pub/file1 .*/
/* 把服务器IP上的文件/home/pub/file1传送到本地当前目录*/

/*./myscp ./dir1/file2 IP:. */
/*把本地当前目录下的子目录dir1中的文件file2传送到服务器ip的当前目录下*/

/*./myscp dir1/file2 IP:/home/pub/ */
/*把本地当前目录下的子目录dir1中的文件file2复制到服务器ip的/home/pub目录下*/

int main(int argc,char *argv[])
{
	int lfd = 0;
	char path[N];
	struct sockaddr_in serv_addr;

	if(argc != 3){
		fputs("para error! please carry para\n",stdout);
		fputs("\t./myscp  xxx.xxx.xxx.xxx:/home/pub/file1  .\n",stdout);
		fputs("\t./myscp  ./dir1/file2  xxx.xxx.xxx.xxx:.\n",stdout);
		fputs("\t./myscp  dir1/file2  xxx.xxx.xxx.xxx:/home/pub/\n", stdout);
		exit(2);
	}else{
		lfd =  sock_init(lfd, serv_addr, SERV_IP);
		sprintf(path, "%s-%s", argv[1], argv[2]);
		write(lfd, path, strlen(path));
		argv_analy(lfd, path);
		close(lfd);
	}

	return 0;
}
