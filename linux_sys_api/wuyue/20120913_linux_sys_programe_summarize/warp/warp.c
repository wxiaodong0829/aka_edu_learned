/*************************************************************************
    > File Name: warp.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月13日 星期四 09时49分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>

void perr_exit(const char *s)
{
	perror(s);
	exit(1);
}

/* fd			:	socket file descripter 
 * sa			:	other side's sockaddr (传出对方地址结构的指针)
 * salenptr		:	length of sa , (传入：你认为 sa 有多长，传出：实际占了多长)
 * return value :	新实例化 的链接的套接字描述符 ,不会返回错误值，出错就直接退出程序，不返回 */
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;
again:
	if ((n = accept(fd, sa, salenptr)) < 0) {
		if ((errno == ECONNABORTED) || (errno == EINTR))
			goto again;
		else{
		//	return -1;
			perr_exit("accept error");
		}
	}

	return n;
}

/* fd: socket file descripter
 * sa: 传给 fd 套接字的 地址结构 指针
 * salen: sa length 
 *										 */
void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		perr_exit("bind error");
}

/* fd: socket file descripter of self
 * sa: other side's struct
 * salen: sa length						*/
void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		perr_exit("Connect error");
}

/* fd: listen socket file descripter 
 * backlog: 最大的链接缓冲区	
 *										*/
void Listen(int fd, int backlog)
{
	if (listen(fd, backlog) < 0)
		perr_exit("listen error");
}

/* family: 通信协议的类型：IPV4, IPV6 , UNIX local
 * type	 : TCP	UDP		
 * protocol:    nomal  is   zero
 * return value: success socket file descripter   */
int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		perr_exit("socket error");
	return n;
}

/* return value:  每次实际读到的个数　不管是否是整个套接字读取的最后一次, 
 *					因为网络环境不同于本机环境，可能在中间时，读取的nbytes,
 *					被拆分为多个网络包进行发送，这些包可能不是一起发来的，
 *					但此函数，阻塞在读上，只要能读，就读取，并返回，不管是否读够　nbytes
 *					*/
ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;
again:
	if ((n = read(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	
	return n;
}

ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n;
again:
	if ((n = write(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else 
			return -1;
	}

	return n;
}

void Close(int fd)
{
	if (close(fd) == -1)
		perr_exit("close error");
}

/* return value: 与上面的　Read 不同，此函数，一直阻塞，
 *				 直到读取足够　ｎ　个字节才返回，
 *				 或者是最后一个数据包，返回值不一定是 n 
 *				 此时，即是套接字文件关闭.
 *				 其余均等到　ｎ　个字节才返回，否则，阻塞在此 Readn() 函数*/
ssize_t Readn(int fd, void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		} else if (nread == 0)
			break;
		nleft -= nread;
		ptr += nread;
	}

	return n - nleft;
}

ssize_t Writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		
		nleft -= nwritten;
		ptr += nwritten;
	}

	return n;
}

static ssize_t my_read(int fd, char *ptr)
{
	static int read_cnt;
	static char *read_ptr;
	static char read_buf[100];

	if (read_cnt <= 0) {
	again:
		if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return -1;
		} else if (read_cnt == 0) /*　文件结尾　*/
			return 0;
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}

/* char *fgets(char *, int size, FILE *stream); 参数同此类似 */
/* 读到　'\0' '\n' 达到最大限制　时，退出.
 * return value:  读一行，读到的字节数,包括'\0'字符, 
 *			   	  如果是'\n' 结尾，结尾处环境是　"...\n\0"   */
ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {				/* １出口：到最大限制*/
		if ((rc = my_read(fd, &c)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;
			if (c == '\0') {
				ptr--;
				break;
			}
		} else if (rc == 0) { /* 文件结尾　*/
			*ptr = 0;
			return n - 1;
		} else 
			return -1;
	}
	*ptr = 0;
	return n;
}

/* witch: 0,read	1,write		2,except	*/
/*	return value == 0, 不可用
				 == 1, 可用
				 == -1  错误*/

int is_readable(int fd, int witch)
{
	fd_set set;
	int n;
	struct timeval t = {0, 0};
	fd_set *r = NULL, *w = NULL, *e = NULL;

	FD_ZERO(&set);
	FD_SET(fd, &set);

	switch (witch) {
		case 0:	r = &set; break;
		case 1: w = &set; break;
		case 2:	e = &set; break;
		default:	return -1;
	}
	n = select(fd + 1, r, w, e, 0);/*n == 0, 不可用
								n == 1, 可用
								n == -1  错误*/
	return n;
}

/* 返回　> 0 : 读到的字符数　
 *	   == -1 : 超时，或其它错误　*/
int read_timeout(int fd, char *buf, int size, int timeout)
{
	fd_set set;
	struct timeval t;
	int n;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	t.tv_sec = timeout;
	t.tv_usec = 0;

	n = select(fd + 1, &set, NULL, NULL, NULL, &t);
	if (n == 1)
		n = read(fd, buf, size);
	else if (n == 0){
		n = -1;
		errno = ETIMEDOUT;
	}

	return n;
}


/**/
int connect_timeout(int sfd, struct sockaddr *addr, 
						socklen_t len, int timeout)
{
	int flags;
	int n;

	flags = fcntl(sfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(sfd, F_SETFL, flags);

	n = connect(sfd, addr, sizeof(addr));
	if (n == 0) { /* 立即返回，不阻塞一个RTT的时间,
					 由于网络很好，立即就链接成功　*/
		flags = fcntl(sfd, F_GETFL);
		flags &= O_NONBLOCK;
		fcntl(sfd, F_SETFL, flags);

		return 0;
	} else if (n == -1) {
		if (errno == EINPROGRESS) { /* 立即返回，
							   此时应阻塞等待链接建立完成　*/
			struct timeval t;
			fd_set set, r, w;

			FD_ZERO(&set);
			FD_SET(sfd, &set);
			r = w = set;
			t.tv_sec = timeout;
			t.tv_usec = 0;
			n = select(sfd + 1, &r, &w, NULL, &t);
			if (n == 0) { /* 没等到数据　*/
				close(sfd);
				errno = ETIMEDOUT;
				return -1;
			} else if (n == 2) { /*说明即可读又可写,即错误*/
				close(sfd);
				return -1;
			} else { /* 一个可用　*/
				if (FD_ISSET(sfd, &w)) {/*成功建立链接*/
					flags = fcntl(sfd, F_GETFL);
					flags &= O_NONBLOCK;
					fcntl(sfd, F_SETFL, flags);

					return 0;
				} else if (FD_ISSET(sfd, &r)) {/*错误*/
					printf("impossable...\n");
				}
			}
		} else {
			close(sfd);
			return -1;
		}
	}
}
