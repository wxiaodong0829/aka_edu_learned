/*************************************************************************
    > File Name: inotify_display.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月28日 星期二 17时31分13秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <signal.h>
#include <err.h>
#include <sys/wait.h>

#include "mem_pool.h"

pid_t *s;

int display(char *dir_name)
{
	DIR *dp;
	struct dirent *p;
	int i;

	if ((dp = opendir(dir_name)) == NULL)
		error_sys("opendir");
	i = 0;
	while((p = readdir(dp)) != NULL) {
		if (p->d_name[0] != '.') {
			printf("%s", p->d_name);
			if (i == 4) {
				i = -1;
				printf("\n");
			} else {
				i++;
				printf(" ");
			}
		}
	}
	printf("\n");

	return 0;
}
void sig_user1(int signo) { }
int watch_dir(char * dir_name)
{
	struct inotify_event *p;
	int ifd; int wd;
	int size, n;
	char buf[BUFSIZ]; 

	if ((ifd = inotify_init()) == -1)
		error_sys("inotify_init");
	wd = inotify_add_watch(ifd, dir_name, IN_CREATE | IN_DELETE);

	while (1) {
		n = read(ifd, buf, BUFSIZ);
		size = 0; p = (struct inotify_event *)buf;
		while (size < n) {
			if (p->mask & IN_CREATE)
				kill(s[0], SIGUSR1);			/*  发送 信号 给 另一个进程 */
			if (p->mask & IN_DELETE)
				kill(s[0], SIGUSR1);

			size += sizeof(struct inotify_event) + p->len;
			p = (struct inotify_event *)&buf[size];
		}
	}

	return 0;
}

int main(int  argc, char ** argv)
{
	pid_t pid;
	int i;
	struct sigaction act;

	if (argc < 2) 
		error_user("usage: ./app dirname");
															/* 共享内存在两个子进程中共享进程ID*/
//	s = (pid_t *)mmap(NULL, sizeof(pid_t) * 2, 
//			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON,
//			-1, 0);
	s = mem_pool(sizeof(pid_t) * 2);
															/* 共享信号处理方式在两个子进程中，捕捉，使慢速系统调用结束阻塞 */
	memset(&act, 0, sizeof(act));
	act.sa_handler = sig_user1;
	sigaction(SIGUSR1, &act, NULL);


	for (i = 0; i < 2; i++) {		/* fork 子进程间共享内存映射，信号处理方式 */
		if ((pid = fork()) == 0)
			break;
		s[i] = pid;
	}
	if (i == 0) {					/* 1th */
		while(1) {
			display(argv[1]);
			pause();
		}

	} else if (i == 1) {			/* 2nd */
		watch_dir(argv[1]);
	} else {					    /* parent */
		for (i = 0; i < 2; i++)
			wait(NULL);
		mem_pool_free();
	}
	return 0;
}
