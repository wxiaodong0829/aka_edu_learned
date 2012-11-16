#include <fcntl.h>

/* 0:read, 1:write, 2:except */

int is_readable(int fd, int witch)
{
	fd_set set;
	int n;
	struct timeval t = {0, 0};
	fd_set *r = NULL, *w = NULL, *e = NULL;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	switch(witch){
	case 0: r = &set; break;
	case 1: w = &set; break;
	case 2: e = &set; break;
	default: return -1;
	}
	n = select(fd + 1, r, w, e, &t);	
	
	return n;
}

int read_timeout(int fd, char *buf, int size, 
	int timeout)
{
	fd_set set;
	struct timeval t;
	int n;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	t.tv_sec = timeout; 
	t.tv_usec = 0;
	
	n = select(fd + 1, &set, NULL, NULL, &t);
	if(n == 1)
		n = read(fd, buf, size);
	else{
		n = -1;
		errno = ETIMEDOUT;
	}

	return n;
}

int main(void)
{
	int sfd;
	struct sockaddr_in addr;
	int flags;

tryagain:
	sfd = socket();

	flags = fcntl(sfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(sfd, F_SETFL, flags); 

	n = connect(sfd, (struct sockaddr *)&addr,	sizeof(addr));
	if(n == -1){ZZ
		if(errno == EINPROGRESS){
			fd_set rset, wset;
			FD_ZERO(&rset); FD_ZERO(&wset);
			FD_SET(sfd, &rset); wset = rset;
			n = select(sfd + 1, &rset, &wset, NULL, NULL);
			if(FD_ISSET(sfd, &wset) && !FD_ISSET(sfd, &rset))
			{
				flags = fcntl(sfd, F_GETFL);
				flags &= ~O_NONBLOCK;
				fcntl(sfd, F_SETFL, flags);

				/* do stuff */
			}else{
				close(sfd);
				goto tryagain;
			}
		}else{
			perror("connect error");
			return -1;
		}
	}


	return 0;
}

int connect_timeout(int sfd, struct sockaddr *addr, socklen_t len, int timeout)
{
	int flags;
	int n;

	flags = fcntl(sfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(sfd, F_SETFL, flags);

	n = connect(sfd, addr, sizeof(addr));
	if(n == 0){
		flags = fcntl(sfd, F_GETFL);
		flags &= ~O_NONBLOCK;
		fcntl(sfd, F_SETFL, flags);

		return 0;
	}else{
		if(errno == EINPROGRESS){
			struct timeval t;
			fd_set set, r, w;

			FD_ZERO(&set);
			FD_SET(sfd, &set);
			t.tv_sec = timeout; t.tv_usec = 0;
			r = w = set;
			n = select(sfd + 1, &r, &w, NULL, &t);
			if(n == 0){
				close(sfd);
				errno = ETIMEDOUT;
				return -1;
			}else if(n == 2){
				close(sfd);
				return -1;
			}else{
				if(FD_ISSET(sfd, &w)){
					flags = fcntl(sfd, F_GETFL);
					flags &= ~O_NONBLOCK;
					fcntl(sfd, F_SETFL, flags);
			
					return 0;
				}else
					printf("impossable...\n");
			}
		}else{
			close(sfd);
			return -1;
		}
	}
}
