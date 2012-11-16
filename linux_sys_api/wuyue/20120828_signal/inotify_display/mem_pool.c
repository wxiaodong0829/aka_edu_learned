/*************************************************************************
    > File Name: memory_pool.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月24日 星期五 17时16分54秒
 ************************************************************************/
#include "mem_pool.h"

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
#if 1
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
#endif

#if 0
void *memory_pool_init()					/*接口设计：不要动原型，可以在此功能模块中高一些辅助函数或变量 如此中的  head */
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
#endif
static char *head = NULL; //glibc 中 strtok() 的实现也是 用了全局变量保存中间值.
/*  只申请一大块空间 */
char *mk_smm(size_t size)
{
	char *p;

	memctl_t mc;
	size_t length = ((size + sizeof(memctl_t))/SIZ_M + 1) * SIZ_M; /*向上取整, 并*/

	mc.left = length - sizeof(memctl_t);

	p = (char *)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	mc.cur = p + sizeof(memctl_t);
	mc.next = NULL;

	*(memctl_t *)p = mc;

	return p;
}
char *get_addr(char *head, size_t size)
{
	char *ret;

	((memctl_t *)head)->left -= size;
	ret = ((memctl_t *)head)->cur;
	((memctl_t *)head)->cur += size;

	PRINT_P(head);
	PRINT(((memctl_t *)head)->left);
	PRINT_P(((memctl_t *)head)->cur);
	PRINT_P(((memctl_t *)head)->next);

	PRINT_P(ret);

	return ret;
}
void *mem_pool(size_t size)
{
	char *ret;
	char *last_mm; //当前块
	char *new_mm;
	char *p;
	if (head == NULL) { /*第一次申请空间`*/

		head = mk_smm(size);

		return get_addr(head, size);
	}

	/*获取此内存池链表的最后一个的首地址给 cur_mm*/
	if (((memctl_t *)head)->next) { /*不止一次申请过空间*/
		for (p = head; ((memctl_t *)p)->next;  p =(char *)((memctl_t *)p)->next) { /*每个池中都检测能否放下此 size 大小*/
			if (((memctl_t *)p)->left >= size) { /*此碎片能放下此 size */
				return  get_addr(p, size);
			}  /*此碎片放不下,继续向下走*/
		}
		last_mm = p; 
	} else			/*只申请过一次空间*/
		last_mm = head;

	/*从当前内存池链表的末尾判断能否放下，还是需要新申请空间*/
	if (((memctl_t *)last_mm)->left >= size) { /*能放得下*/ 
		ret = get_addr(last_mm, size);
	} else { /*放不下，需要另外申请空间*/
		new_mm = mk_smm(size);
		((memctl_t *)last_mm)->next = (memctl_t *)new_mm;

		ret = get_addr(new_mm, size);
	}

	return ret;
}
/* return :  success:0    fail: -1*/
int get_size(char *head)
{
	return ((memctl_t *)head)->left + (((memctl_t *)head)->cur - head);
}
int mem_pool_free(void)
{
	char *p, *q;
	size_t size;
	if (head == NULL)
		return 0;

	if (((memctl_t *)head)->next == NULL) {
	 //只有一个池
		p = head;
		size = get_size(head);
		if (sfree(head, size) == -1)
				error_sys("sfree failed");
		return 0;
	}

	for (p = head; p; p = q) {
		q = (char *)((memctl_t *)p)->next;
		size = get_size(p);
		if (sfree(p, size) == -1)
				error_sys("sfree failed");
	}
	return 0;
}


#ifdef DEBUG_MEM_POOL 
int main(void)
{
	pid_t pid;
	int i;
	int n = 2;
	char buf[BUFSIZ];
	char *b;
	int size;
	char *p;

#if DEBUG_MEM_POOL == 2
	while (1) {
		b = fgets(buf, BUFSIZ, stdin);
		buf[strlen(b) - 1] = '\0';
		if (strcmp(b, "q") == 0)
			break;
		size = atoi(buf);
		
		p = mem_pool(size);
	}
	mem_pool_free();
#endif


#if DEBUG_MEM_POOL == 1								/* 匿名 内存 映射区, 用于有 父子，兄弟 关系的进程*/
	int *p, *q;

	p = (int *) memory_pool(4084);
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
	mem_pool_free();
#endif

	return 0;
}
#endif
