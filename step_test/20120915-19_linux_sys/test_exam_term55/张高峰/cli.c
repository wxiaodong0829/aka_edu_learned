#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 8000

err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int sock_init(struct sockaddr_in addr,const char *ip){
	int sfd,n;
	inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);	
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("sock_init socket error");
	if((n = connect(sfd, (struct sockaddr *)&addr, sizeof(addr))) < 0){
		err_sys("sock_init connect error");
	}else
		return sfd;
}

int main(int argc,char *argv[]){
	char *t,*p,*q,*r,buf[1024];	
	struct stat st;
	struct sockaddr_in servaddr;
	int fd,cfd,n;
	if(argc != 3)
		err_sys("input error");
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	p = argv[1];
	q = argv[2];
	t = strchr(p, ':');
	if(t == NULL){
		stat(p,&st);			
		if(S_ISREG(st.st_mode)){
			if((fd = open(p,O_RDONLY)) < 0){
				err_sys("open err");
			}
		}else
			err_sys("not found file");
			r = strchr(q,':');
			t = r;
			r++;
			*t = '\0';
		cfd = sock_init(servaddr,q);
		t = strrchr(p,'/');
		t++;
		sprintf(buf,"up %s/%s",r,t);
		write(cfd,buf,strlen(buf));
		n = read(cfd,buf,1024);
		buf[n] = '\0';
		if(strncmp(buf,"ok",2) == 0){
			while((n = read(fd, buf, 1024)) != 0){
				write(cfd,buf,n);
			}	
		}else
			err_sys("server error or server dir not found");
	}else{
		*t = '\0';
		t++;
		cfd = sock_init(servaddr,p);
		r = strrchr(t,'/');
		r++;
		sprintf(buf,"%s/%s",q,r);
		if((fd = open(buf,O_RDWR | O_CREAT | O_TRUNC,0644)) < 0){
			err_sys("open err");
		}
		sprintf(buf,"down %s",t);
		write(cfd,buf,strlen(buf));
		n = read(cfd,buf,2);
		buf[n]= '\0';
		if(strncmp(buf,"ok",2) == 0){
			while((n = read(cfd,buf,1024)) != 0){	
				write(fd,buf,n);
			}
		}else
			err_sys("ser no found file");

	}	
		close(cfd);
		close(fd);

		return 0;
}
