/*************************************************************************
    > File Name: pthread_copy.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月30日 星期四 15时52分48秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "err.h"
typedef struct {
	int index;
	int fd_s;
	int fd_d;
	char *mmap_s;
	char *mmap_d;
	int len;
	int total;//long long total;
}arg_t;

volatile arg_t *p;
int copy(void *index, void *len)
{
	int i;
	int end = (int)len + (int)index;

	for (i = (int)index; i < (int)end && i < p->total; i++)
	{
		p->mmap_d[i] = p->mmap_s[i];
	}
	return 0;
}
void *ptr_fn(void *index)
{
	copy(index, (void *)p->len);
	return 0;
}
/* ./app src dest [n] */
int main(int argc, char **argv)
{
	int n = 5, i, j;
	off_t m_off_s = 0, m_off_d = 0;
	//size_t size = 1024 * 1024;
	int err;
	size_t size = 1024 * 4;
	int  left_size;

	if (argc == 4)
		n = atoi(argv[3]);

	pthread_t tid[n];
	memset(tid, 0,sizeof(tid));
//	tid = malloc(sizeof(*tid) * n);

	p = malloc(sizeof(*p));
	memset((void *)p, 0, sizeof(*p));

	if ((p->fd_s = open(argv[1], O_RDWR)) == -1) //以大文件方式打开
		error_sys("open src");
	if ((p->fd_d = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1) //以大文件方式打开
		error_sys("open dest");

	left_size = lseek(p->fd_s, 0, SEEK_END);
	p->total = left_size;
	lseek(p->fd_d, left_size - 1, SEEK_SET);
	write(p->fd_d, "0", 1);
	while (left_size > 0) { //文件结尾处跳出
		p->mmap_s = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, p->fd_s, m_off_s);
		if (p->mmap_s == MAP_FAILED)
			error_sys("mmap src");
		m_off_s += size;
		p->mmap_d = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, p->fd_d, m_off_d);
		if (p->mmap_d == MAP_FAILED)
			error_sys("mmap dest");
		m_off_d += size;

		PTHREAD_THREADS_MAX;
		p->index = 0;
		p->len = ((int)size)/(n);
		for (i = 0; i < n - 1; i++) {
			err = pthread_create(&tid[i], NULL, ptr_fn, (void *)p->index); //这是个在变化的值p->index,
			if (err != 0) {
				printf("%dth child\n", i);
				perror("pthread_create");
			}
			p->index += p->len;
		}

		for (j = 0; j < n - 1; j++) {
			err = pthread_join(tid[j], NULL);			/*  381 个子线程时出现段错误*/
			if (err != 0)
				perror("pthread_join");
		}
		copy((void *)p->index, (void *)(p->len + size%n));

		munmap(p->mmap_s, size);
		munmap(p->mmap_d, size);

		left_size -= size;
	}
	close(p->fd_s);
	close(p->fd_d);
	return 0;
}
