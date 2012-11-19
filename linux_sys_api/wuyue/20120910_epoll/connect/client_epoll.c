#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include "err.h"

#define ROOT "./cli"        /* 要下载到的地方的根目录 */

							/* 状态机 */
#define CONN 1             /* 链接的状态  链接   下载   搞定 */
#define READ 2
#define DONE 3

#define offsetof(type, member) (size_t) (&((type *)0)->member)

#define containerof(ptr, type, mem) \
		(type *)((char *)ptr - offsetof(type, mem))

struct myfile	/* 一个下载所需的属性 */
{
	char *filename;		/* 要下载的文件名 */
	int fd;				/* 本地文件的描述符*/
	int cfd;			/* 下载此文件所需的链接的客户端套接字 文件描述符*/
	int status;			/* 描述 一个链接(客户端，服务器端 双方 的ip,port 共同形成) 的状态.
						   0 1 2 3 分别对应：初始态 链接态 下载态 完成态     
						   扩展 为指定链接数，因为链接数与速度，是抛物线 ，不是越多越好,因此用 select, 而不用 epoll */
};

/* ./app file1 file2 file3 ... */
/* 维护的内容， 1,下载属性   2,select位图集 3, 并发提出链接申请原理：使套接字 不阻塞
 * 此程序 使用状态机的机制 使 并发链接 和 并发接收数据 完全分离 */
int main(int argc, char *argv[])
{
	int sfd,	/* 用于暂存每次创建的 发送链接后，套接字文件描述符 */
		fd;		/* 用于暂存打开的要下载的文件描述符*/
	struct sockaddr_in serv_addr;	/* IPV4 地址结构的变量 */
	int n, i, 
		flags;	/* 暂存文件属性标志 */
	int res, 
		nread,  /* 从网络套接字中读到的字节数*/
		nleft;	/* 剩余 的 等待传输文件的链接个数*/
	struct myfile *list;			/* 要传输的文件结构的数组的指针*/
	struct epoll_event ep;
	struct epoll_event events[FD_SETSIZE];
	int efd;
	int nready, j;


	n = argc - 1;												/* 初始化要创建的下载文件的个数 */
	list = (struct myfile *)malloc(sizeof(struct myfile) * n);	/* 为要传输的文件结构的数组分配空间 */
	for(i = 0; i < n; i++){										/* 初始化此数组 */
		list[i].filename = argv[i + 1];
		list[i].fd = -1;
		list[i].cfd = -1;
		list[i].status = 0;	/* 初始态 */
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));					/* 初始化网络地址结构 */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	memset(events, 0, sizeof(events));
	efd = epoll_create(FD_SETSIZE);
	if (efd == -1)
		error_sys("epoll_create");


	for(i = 0; i < n; i++){					/* -----------   并发 发起 链接 只处理链接请求，三次链接之前 --------- */
		sfd = socket(AF_INET, SOCK_STREAM, 0);					/* */
		list[i].cfd = sfd;

		flags = fcntl(sfd, F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(sfd, F_SETFL, flags);
		
		res = connect(sfd, (struct sockaddr *)&serv_addr,	/* 并发提出链接申请原理：使套接字 不阻塞 */
				sizeof(serv_addr));
		if(res == -1){
			if(errno != EINPROGRESS){							/* 请求确实错误 */
				perror("connect error");
 				return -1;
			}													/* else 进入并发发送链接请求的逻辑 */
			list[i].status = CONN;								/* 链接态  链接 */
			
			ep.events = EPOLLIN | EPOLLOUT, ep.data.fd = sfd;				/* 添加让 epoll 关心的事件 */
			res = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ep);
			if (res == -1)
				error_sys("epoll_ctl1");

//			ep.events = EPOLLOUT, ep.data.fd = sfd;
//			res = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ep);
//			if (res == -1)
//				error_sys("epoll_ctl2");
		}else if(res == 0){										/* 链接请求，立即成功建立链接，善后处理，为接收普通数据做准备*/
			char path[1024];
			
			list[i].status = READ;								/* 下载态  链接 */

			flags = fcntl(sfd, F_GETFL);						/* 将 套接字的 文件属性 还原为 正常阻塞 */
			flags &= ~O_NONBLOCK;
			fcntl(sfd, F_SETFL, flags);
			
												/* 让 select 关心此新建立的链接的客户端的套接字文件 */
			ep.events = EPOLLIN, ep.data.fd = sfd;
			res = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ep);
			if (res == -1)
				error_sys("epoll_ctl3");
			write(sfd, list[i].filename,						/* 发给 服务器 要下载的文件名 */
					strlen(list[i].filename));

			sprintf(path, "%s/%s", ROOT, list[i].filename);		/* 客户端 建立一个 等待要下载的文件的内容的 空瓶子，
																								等着服务器向里面注水 */
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			list[i].fd = fd;
		}
	}
						/*------------------- 统一 检测所有文件 ,处理三次握手之后 的 数据接收 ---------------------*/
	nleft = n;
	while(nleft > 0){
	//	printf("hello\n");
		nready = epoll_wait(efd, (struct epoll_event *)&events, FD_SETSIZE, -1);
		if (nready == -1)
		error_sys("epoll_wait");
	//	printf("world\n");

		for(j = 0; j < nready; j++){ /*  有几个事件 发生 */
			if (events[j].events == EPOLLIN) {
				for (i = 0; i < n; i++) {
					if (events[j].data.fd == list[i].cfd) {
						if (list[i].status == CONN) {
							return -1;/* 链接失败，需要重传 */
						} else if (list[i].status == READ) {
							char buf[1024];
							nread = read(list[i].cfd, buf, 1024);
							if(nread == 0){							/* 对方将他的链接端关闭 ,即文件传输完毕 */
								close(list[i].cfd);					/* 将此下载 的各属性 善后 */
								close(list[i].fd);
								list[i].status = DONE;				/* 使此 套接字 不再进入 for 中进行数据处理 */

								ep.events = EPOLLIN, ep.data.fd = list[i].cfd;
								epoll_ctl(efd, EPOLL_CTL_DEL, list[i].cfd, &ep);/* 取消 select 的关心 */

								printf("%s done...\n", list[i].filename);
								nleft--;							/* 当此时的套接字文件关闭后，才减 1，使while 逼近结束一步 */
							}else									/* 普通数据 写到本地，将对方的水倒入自己的瓶子 */
								write(list[i].fd, buf, nread);
						} else if (list[i].status == DONE)
							return -1;
					}
				}
			} else if (events[j].events == EPOLLOUT) {
				for (i = 0; i < n; i++) {
					if (events[j].data.fd == list[i].cfd) {
						if (list[i].status == CONN) {
								char path[1024];
			
								list[i].status = READ;				/* 将下载 状态 更改为  下载 */

								flags = fcntl(list[i].cfd, F_GETFL);
								flags &= ~O_NONBLOCK;
								fcntl(list[i].cfd, F_SETFL, flags);
			
								ep.events = EPOLLOUT | EPOLLIN, ep.data.fd = list[i].cfd;
								res = epoll_ctl(efd, EPOLL_CTL_DEL, list[i].cfd, &ep);
								if (res == -1)
									error_sys("epoll_ctl4");

								ep.events = EPOLLIN, ep.data.fd = list[i].cfd;
								res = epoll_ctl(efd, EPOLL_CTL_ADD, list[i].cfd, &ep);
								if (res == -1)
									error_sys("epoll_ctl4");
								res = write(list[i].cfd, list[i].filename, strlen(list[i].filename));
			
								sprintf(path, "%s/%s", ROOT, list[i].filename);
								fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
								list[i].fd = fd;
						} /* else if (list[i].status == READ) 可添加对写操作的控制 */
					}
				}
			} else if (events[j].events == (EPOLLIN | EPOLLOUT))
				return -1;
		}
	}
		printf("one round is over...\n");

	return 0;
}
