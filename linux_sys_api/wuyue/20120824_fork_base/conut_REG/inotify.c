/*************************************************************************
    > File Name: inotify.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月23日 星期四 15时54分18秒
 ************************************************************************/

#include <stdio.h>
#include "err.h"
#include <unistd.h>
#include <sys/inotify.h>


int main(void)
{
	int ifd, //虚拟的 监视器 文件描述符
		n,		//从ifd监视器中读到的字符数
		size;
	char buf[1024];
	struct inotify_event *p;

	ifd = inotify_init();
	if (-1 == ifd)
		error_sys("inotify_init error");
	n = inotify_add_watch(ifd, ".", IN_CREATE | IN_DELETE);
	if (-1 == n)
		error_sys("inotify_add_watch error");
	while (1) {
		n = read(ifd, buf, 1024);
		size = 0;
		p = (struct inotify_event *)buf;
		while (size < n) {
			if (p->mask & IN_CREATE) {
				if (p->len > 0) 
					printf("wd:%d %s create\n", p->wd, p->name);
			} else
				printf("wd:%d other...\n", p->wd);
			size = size + sizeof(struct inotify_event) + p->len;
			p = (struct inotify_event *)(buf + size);
		}
	}
	return 0;
}
