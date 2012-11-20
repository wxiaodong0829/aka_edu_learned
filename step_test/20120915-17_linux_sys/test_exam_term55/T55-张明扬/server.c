#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int lfd, cfd, fd, n;
	char buf[1024], path[1024], dir[1024];
	struct sockaddr_in serv_addr, cliaddr;
	socklen_t cliaddr_len;

	lfd = socket(AF_INET, SOCK_STREAM, 0); /*监听套接字*/
	if(lfd == -1)
		err_sys("socker error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(n == -1)
		err_sys("bind error");
	n = listen(lfd, 20);
	if(n == -1)
		err_sys("listen error");

	while(1){
		cfd = accept(lfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		if(cfd == -1)
			err_sys("accept error");
			
		n = read(cfd, buf, 1024);
		if(n == -1)
			err_sys("read error");
		buf[n] = '\0';

		if(n == 0) /*客服端关闭连接*/
			close(cfd);
		else{
			struct stat tmp;		

			n = stat(buf, &tmp);/*判断下载还是上传(文件or目录)*/
			if(n == -1)
				err_sys("stat error");

			if(S_ISREG(tmp.st_mode)){ /*下载*/
				fd = open(buf, O_RDONLY);
				if(fd == -1)
					err_sys("open error");

				while(n = read(fd, buf, 1024))
					write(cfd, buf, n);

				printf("download done...\n");
				
				close(cfd);
				close(fd);
			}
			else if(S_ISDIR(tmp.st_mode)){ /*上传*/
				strcpy(dir, buf);

				write(cfd, "OK", 3);//应答客服端 ，等待客服端传送文件名
				
				n = read(cfd, buf, 1024);//接收文件名
				if(n == -1)
					err_sys("read error");

				write(cfd, "OK", 3);//应答客服端 ，等待客服端传送文件内容

				sprintf(path, "%s/%s", dir, buf);//形成路径

				fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(n == -1)
					err_sys("open error");
				while(n = read(cfd, buf, 1024))
					write(fd, buf, n);

				printf("%s is added...\n", path);
				
				close(cfd);
				close(fd);
			}
		}
	}

	close(lfd);
	return 0;
}
