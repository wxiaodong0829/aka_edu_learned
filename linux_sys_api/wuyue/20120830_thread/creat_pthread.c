/*************************************************************************
    > File Name: creat_pthread.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月30日 星期四 10时58分34秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x) \n", s, (unsigned int )pid, 
			(unsigned int)tid, (unsigned int )tid);
}
void *thr_fn(void *arg)
{
	printids(arg);
	return NULL;
}
int main(void)
{
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, "new thread: ");
	if (err != 0) {
		fprintf(stderr, "can/t create thread: %s\n", strerror(err));
		exit(1);
	}
	printids("main thread: ");
	sleep(1);

	return 0;
}
