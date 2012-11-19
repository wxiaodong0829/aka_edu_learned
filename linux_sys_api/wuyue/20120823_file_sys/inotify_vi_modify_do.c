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
	//n = inotify_add_watch(ifd, ".", IN_CREATE | IN_DELETE);
	n = inotify_add_watch(ifd, ".", IN_ALL_EVENTS);
	if (-1 == n)
		error_sys("inotify_add_watch error");
	while (1) {
		n = read(ifd, buf, 1024);
		size = 0;
		p = (struct inotify_event *)buf;
		while (size < n) {
			if (p->mask & IN_ACCESS) {
				if (p->len > 0) 
					printf("wd:%d %s access read\n", p->wd, p->name);
			} else if (p->mask & IN_ATTRIB) {
				if (p->len > 0) 
					printf("wd:%d %s metadata changed\n", p->wd, p->name);
			} else if (p->mask & IN_CLOSE_WRITE) {
				if (p->len > 0) 
					printf("wd:%d %s file opened for writing was closed\n", p->wd, p->name);
			} else if (p->mask & IN_CLOSE_NOWRITE) {
				if (p->len > 0) 
					printf("wd:%d %s file not opened for writing was closed\n", p->wd, p->name);
			} else if (p->mask & IN_CREATE) {
				if (p->len > 0) 
					printf("wd:%d %s file/directory created in watched directory\n", p->wd, p->name);
			} else if (p->mask & IN_DELETE) {
				if (p->len > 0) 
					printf("wd:%d %s file/directory deleted from watched directory\n", p->wd, p->name);
			} else if (p->mask & IN_DELETE_SELF) {
				if (p->len > 0) 
					printf("wd:%d %s watched file/directory was itselef deleted\n", p->wd, p->name);
			} else if (p->mask & IN_MODIFY) {
				if (p->len > 0) 
					printf("wd:%d %s file was modified\n", p->wd, p->name);
			} else if (p->mask & IN_MOVE_SELF) {
				if (p->len > 0) 
					printf("wd:%d %s watched file/directory was itself moved\n", p->wd, p->name);
			} else if (p->mask & IN_MOVED_FROM) {
				if (p->len > 0) 
					printf("wd:%d %s file moved out of watched directory\n", p->wd, p->name);
			} else if (p->mask & IN_MOVED_TO) {
				if (p->len > 0) 
					printf("wd:%d %s file moved into watched directory\n", p->wd, p->name);
			} else if (p->mask & IN_OPEN) {
				if (p->len > 0) 
					printf("wd:%d %s file was opened\n", p->wd, p->name);
			} else if (p->mask & IN_DONT_FOLLOW) {
				if (p->len > 0) 
					printf("wd:%d %s IN_DONT_FOLLOW\n", p->wd, p->name);
			} else if (p->mask & IN_MASK_ADD) {
				if (p->len > 0) 
					printf("wd:%d %s add events to watch mask for this pathname if it already exists \n", p->wd, p->name);
			} else if (p->mask & IN_ONESHOT) {
				if (p->len > 0) 
					printf("wd:%d %s monitor pathname for one event,then remove from watch list\n", p->wd, p->name);
			} else if (p->mask & IN_ONLYDIR) {
				if (p->len > 0) 
					printf("wd:%d %s only watch pathname if it is a directory\n", p->wd, p->name);
			} else if (p->mask & IN_IGNORED) {
				if (p->len > 0) 
					printf("wd:%d %s IN_IGNORED\n", p->wd, p->name);
			} else if (p->mask & IN_ISDIR) {
				if (p->len > 0) 
					printf("wd:%d %s is a directory\n", p->wd, p->name);
			} else if (p->mask & IN_Q_OVERFLOW) {
				if (p->len > 0) 
					printf("wd:%d %s event queue overflowed\n", p->wd, p->name);
			} else if (p->mask & IN_UNMOUNT) {
				if (p->len > 0) 
					printf("wd:%d %s file system containing watched object was unmounted\n", p->wd, p->name);
			} else 
				printf("wd:%d other...\n", p->wd);
			size = size + sizeof(struct inotify_event) + p->len;
			p = (struct inotify_event *)(buf + size);
		}
	}
	return 0;
}
