/*************************************************************************
    > File Name: chat_room.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年09月11日 星期二 20时58分24秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "err.h"
#include "debug.h"

#define BUFSIZE 1024

#define UP 1
#define DOWN 2

#define DO 1
#define DONE 2 

typedef struct usr {
	struct sockaddr_in addr;	/* 对应的地址结构 */
	int type;					/* 1:上传，2:下载*/
	int status;					/* 状态机 */
	int socket;					/* 只下载用 对方套接字*/
	int fd;						/* 本地文件描述符 */
	struct usr *next;			/* 简单的 链表操作 */
}usr_t;

usr_t * head = NULL;

usr_t *new_node(const struct sockaddr_in *addr)
{
	usr_t *p;

	p = malloc(sizeof(usr_t));
	if (p == NULL)
		return NULL;
	
	p->addr = *addr;
	p->type = 0;
	p->status = 0;
	p->socket = -1;
	p->fd = -1;
	p->next = NULL;

	return p;
}

int insert(const usr_t * p)
{
	usr_t *q;

	if (p == NULL)
		return -1;
	if (head == NULL) {
		head = p;
		return 0;
	}
	for (q = head; q->next != NULL; q = q->next)
		;
	q->next = p;

	return 0;
}

int is_equal(struct sockaddr_in *p, struct sockaddr_in *q)
{
	return p->sin_family == q->sin_family && 
		   p->sin_port ==	q->sin_port  &&
		   p->sin_addr.s_addr == q->sin_addr.s_addr;
}

usr_t * search_by_addr(struct sockaddr_in *addr)
{
	usr_t *p;

	for (p = head; p != NULL; p = p->next)
		if (is_equal(&p->addr, addr))
			return p;

	return NULL;
}
void delete_by_addr(struct sockaddr_in *addr)
{
	usr_t *p, *q;
	
	if (is_equal(&head->addr, addr)) {
		p = head;
		head = head->next;
		free(p);
		return ;
	}

	for (p = head; p->next != NULL; p = p->next) {
		if (is_equal(&p->next->addr, addr)) {
			q = p->next;
			p->next = p->next->next;
			free(q);
			return ;
		}
	}
}

void print(void)
{
	usr_t *p;
	char ip[20];

	for (p = head; p != NULL; p = p->next) {
		if (p->type == UP)
			printf("UP  client ---file-sendto-server---> server, ");
		else if (p->type == DOWN)
			printf("DOWN  server ---file-sendto-client---> client, ");
		inet_ntop(AF_INET, &p->addr.sin_addr.s_addr, ip, 20);
		printf("client_ip: %s, ", ip);
		printf("client_port: %u", ntohs(p->addr.sin_port));
		printf("fd:%d, ", p->fd);
		if (p->status == DO)
			printf("status: DO\n");
		else if (p->status == DONE)
			printf("status: DONE\n");
		else
			printf("status: impossible...\n");
	}
}

void destroy(void)
{
	usr_t *p, *q;

	for (p = head; p != NULL; p = q) {
		q = p->next;
		free(p);
	}

	head = NULL;
}

int sock_init(in_port_t port, const char *ip)
{
	int sfd;
	struct sockaddr_in serv_addr;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sfd == -1) {
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

	if (bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		return -1;

	return sfd;
}


int is_end(char *buf)
{
	if (strncmp(buf, "UP_END", 6) == 0){ /* 收到  结束 */

		return 1;
	}
	return  0;
}
#define MODE_LEN 5
#define FILE_LEN 255
#define ROOT "./serv"
/* 前三个是传出参数*/
int fill_struct(int *type, int *status, int *fd, char *buf)
{
	char mode[MODE_LEN]; char filename[FILE_LEN];
	char path[FILE_LEN];
	char *p;
	int i; int file_d;
	char root[FILE_LEN];
	struct stat st;

	for (p = buf, i = 0; p = strtok(p, " "); p = NULL, i++) {
		if (i == 0) {
			strncpy(mode, p, strlen(p) + 1);
		} else if (i == 1) {
			strncpy(root, p, strlen(p) + 1);
		} else if (i == 2)
			strncpy(filename, p, strlen(p) + 1);
	}
	sprintf(path, "%s/%s", root, filename);
	PRINT_S(path);

    lstat(path, &st);
	if(S_ISDIR(st.st_mode)) {
		printf("%s is dir file\n", path);
		return -1;
	}

	if (strcmp(mode, "up") == 0) {           /* 上传文件 */
		*type = UP;
		*fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*fd == -1)
			error_sys("open up");
		*status = DO;
	}
	else if (strcmp(mode, "down") == 0) {    /* 下载文件 */
		*type = DOWN;
		*fd = open(path, O_RDONLY);
		if (*fd == -1)
			error_sys("open up");
		*status = DO;
	}

	return 1;
}
int main(void)
{
	int sfd, n, nsend;
	char buf[BUFSIZE];
	usr_t *p;
	socklen_t len;
	struct sockaddr_in cli_addr;
	ssize_t nrecv;

	sfd = sock_init(8000, "127.0.0.1");
	if (sfd == -1)
		error_sys("sock_init");

	while (1) {
		n = sizeof(cli_addr);
		nrecv = recvfrom(sfd, buf, BUFSIZE, MSG_DONTWAIT, 
				(struct sockaddr *)&cli_addr, &n);
		if (nrecv == -1) {                                    /* 0：表示对方 还是 自己 有序关闭 */
			if (errno != EAGAIN && errno != EWOULDBLOCK)
				error_sys("recvfrom");
		} else if (nrecv == 0) {
			printf("\n???????why is here ?????\n");
		} else if (nrecv > 0) {													/*  有数据可读  */
			p = search_by_addr(&cli_addr);
			if (p != NULL) { /* 找到了，说明是 客户端上传的文件的内容 */    /*  处理上传数据 */
				if (is_end(buf)) {
//					sendto(sfd, "OK", strlen("OK"), 0, 
//							(struct sockaddr *)&p->addr, sizeof(p->addr));
					close(p->fd);
					delete_by_addr(&p->addr);
				} else 
					write(p->fd, buf, nrecv); /* 用什么作为结束标志呢 ............................?????????????????*/
			} else {		/* 需要新添的 传输 */
//				sendto(sfd, "OK", strlen("OK"), 0, 
//			 	 (struct sockaddr *)&cli_addr, sizeof(cli_addr));
				buf[nrecv] = '\0';						/* 判断是那种方式 , 并填充 结构体 */
				printf("%s\n",buf);
				usr_t *new;
				new = new_node(&cli_addr);
				n = fill_struct(&new->type, &new->status, &new->fd, buf);
				if (n == -1)
				sendto(sfd, "DOWN_END", strlen("DOWN_END"), 0, 
			 	 (struct sockaddr *)&cli_addr, sizeof(cli_addr));
				
				insert(new);
			}
		}
		for (p = head; p != NULL; p = p->next) {						 /* 处理 下载*/
			if (p->type == DOWN) {
				n = read(p->fd, buf, BUFSIZE);
				if (n == 0) { /* 要下载的文件结束  */
	//			tryagain:
					PRINT_S("sendto down_end");
					n = sendto(sfd, "DOWN_END", strlen("DOWN_END"), 0, (struct sockaddr *)&p->addr, sizeof(p->addr));

					close(p->fd);
					delete_by_addr(&p->addr);
#if 0
					n = recvfrom(sfd, buf, 1024, 0, NULL, NULL);
					buf[n] = '\0';
					if (strcmp(buf, "OK")) {
						sleep(1);		/* 等待因网络原因产生的数据无法到达*/
						printf("fail to logout...\n");
						goto tryagain;
					}
#endif
				} else {
					nsend = sendto(sfd, buf, n, 0, 
							(struct sockaddr *)&p->addr, sizeof(p->addr));
				}
			}
		}
//		print();
	}

	destroy();

	return 0;
}

