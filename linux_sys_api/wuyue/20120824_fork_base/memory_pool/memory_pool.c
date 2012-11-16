/*************************************************************************
    > File Name: memory_pool.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 17时16分54秒
 ************************************************************************/

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
/*******************************
 *
 * 申请一块　匿名映射区
 * return :     成功：返回此映射区的首地址 void * 泛型指针
 *				失败：返回　NULL
 * size   :		要申请的空间的大小
 *
 *
 *
 * **************************/
void * smalloc(size_t size) 
{
	char * p;

	p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (p == MAP_FAILED)
		return NULL;

	return p;
}
/**************
 *
 * 释放　匿名映射区　　ｓ表示共享，主要用于父子进程间的共享
 * return : 同　munmap();
 *
 * ***********/
int sfree(void *addr, size_t length)
{
	return	munmap(addr, length);
}
struct mem_ctl {
	int left;	// 此４Ｋ还剩多少
	char *cur;	//　当前指向何处
	struct mem_ctl *next; //下一块４Ｋ的地址
};
#define SIZ_M 4096
void *memory_pool_init()
{
	char *head;
	struct mem_ctl mem;

	head = smalloc(SIZ_M);

	if (head == NULL)
		return NULL;

	mem.left = SIZ_M - sizeof(mem);
	mem.cur = (char *)(head + sizeof(mem));
	mem.next = NULL;
	
	*head = mem;

	return head;
}
void *memory_pool(size_t size, char *head)
{
	char *ret;
	if (size < SIZ_M && *(head) - size > 0) { /*	size 小于	4K */
		if (*(head) - size > 0) {
			*(head) -= size; 
			ret = *(head + 4);
			*(head + 4) =  *(char *)(head + 4) + size; 
			return ret;
		} else {
			insert(head, )
		}
	} else { /*	size 大于	4K */
	}
}

int mpfree(void *addr, size_t length)
{
}
#if DEBUG
int main(void)
{
	pid_t pid;
	int i;
	int n = 2;

	int *p;

	p = (int *) smalloc(sizeof(*p));

	*p = 100;

	for (i = 0; i < n; i++)
		if ((pid = fork()) == 0)
			break;

	if (i == n) { /* parent */
		sleep(1);
		printf("*p = %d\n", *p);
	} else { /* child */
		*p = 200;
	}

	return 0;
}
#endif
