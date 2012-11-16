/*************************************************************************
    > File Name: count_REG.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 11时14分24秒
 ************************************************************************/
/******************************
 * describe: 
 *			1，链接文件，不区分 链接的目的地 是目录，还是其它文件
 *
 *
 *
 *
 *
 ***************************/
int count_REG(const char * pathname);
#if 0
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	struct stat st;
	lstat(argv[1], &st);
	if (S_ISLNK(st.st_mode))
		printf("%s is a symbolic link", argv[1]);

	return 0;
}
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "err.h"

int main(void)
{
	int ifd, //虚拟的 监视器 文件描述符
		n,		//从ifd监视器中读到的字符数
		size;
	int REG_count;
	char buf[1024];
	struct inotify_event *p;

	REG_count = count_REG(".");
	printf("REG_count: %d\n", REG_count);

#ifndef DEBUG
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
		REG_count = count_REG(".");
		printf("REG_count: %d\n", REG_count);
	}
#endif 
	return 0;
}

int count_REG(const char * pathname)
{
	int count;
	char file_name_buf[256];

	struct dirent *p_read;
	DIR *dirp;

	struct stat st;


	if ((dirp = opendir(pathname)) == NULL)
		error_sys("opendir");

	count = 0;
	while ((p_read = readdir(dirp)) != NULL) {
		if (strcmp(p_read->d_name, ".") == 0 || strcmp(p_read->d_name, "..") == 0 )
			continue;
		sprintf(file_name_buf, "%s/%s", pathname, p_read->d_name);
		lstat(file_name_buf, &st);
		if (S_ISREG(st.st_mode))
			count++;
		if (S_ISDIR(st.st_mode))
			count += count_REG(file_name_buf);
	}
	closedir(dirp);
	return count;

}
