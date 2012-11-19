#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 2

sem_t empty, full;	/* 第一组：控制  生产者    消费者 */
sem_t avail;		/* 第二组：控制  线程池				*/
volatile int cfd;

void *tfn(void *arg)	/* 工人工作流程 */
{
	int sfd; //工人接袋子的口袋
	int n, i;
	char buf[1024];
	int val;

	while(1){
		printf("%u waiting\n", (unsigned)pthread_self());/* 报告自己在粮仓门口等着呢 */
		
		sem_wait(&full);   /*在粮仓门口等着收割机开进粮仓后的 仓门敞开,						开始时， 阻塞在此
							 因为是竞争上岗,											当full为1时	惊群唤醒所有工人
							 所有人一视同仁,早干活,早有可能得到长工机会*/
		sfd = cfd;			/* 伸手去 接收割机上的存放玉米的袋子 ,此时粮仓不可用*/
		sem_post(&empty);	/* 关闭粮仓门，即有可用粮仓*/

		printf("%u working\n", (unsigned)pthread_self());/* 报告自己将要去工作 */
		while(1){								/* 工作，直至做完*/
			n = read(sfd, buf, 1024);
			if(n == 0)							/* 工作做完了*/
				break;
			for(i = 0; i < n; i++)
				buf[i] = toupper(buf[i]);
			write(sfd, buf, n);
		}
		close(sfd);								/* 将袋子上交东家*/

		sem_getvalue(&avail, &val);						/*竞争上岗，看看是否有岗位，即长工人数够要求的数量吗*/
		if(val >= MAX)												/* 工人已经够了 */
			break;													/* 离开，工作辞退*/
		sem_post(&avail);											/* 工人不够，入职成为长工 */
	}

	printf("%u exit\n", (unsigned)pthread_self());		/* 感慨一句，我要走了...   而且不带走一片云彩*/

	return 0;																		/* 资源回收 */
}
/*
 * 主函数：
 *	初始化 网络服务
 *	初始化 需要雇用的长工 avail
 *			粮仓空(一个仓门关闭)empty			粮仓满(一个仓门打开)full     ( 仅一个粮仓 )
 *	雇用长工 MAX 个
 *
 *	again:
 *		等待玉米成熟					accept
 *		当玉米成熟后，用收割机收割		sfd = accept
 *		等待一个空粮仓,等到一个空粮仓后 wait(&empty)
 *		将收割机从田里开进粮仓 cfd			cfd = sfd;
 *		敞开粮仓大门					post(&full)
 *		   //由于工人很积极，都等在门外，立刻有一个工人紧跟着进入粮仓，收割机将收割中存放玉米穗的口袋交给工人,工人独自去干活
 *		看看长工够不够，不够就雇用短工
 *		goto again;
 *
 *主函数 有可能阻塞的地方：     accept ,wait(&empty)   即：等玉米成熟， 等粮仓可用（仓门关闭，表可用empty为1）
 *
 * */
int main(void)
{
	int lfd, sfd, i, n;
	struct sockaddr_in serv_addr;
	pthread_t tid;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	listen(lfd, 20);

	sem_init(&empty, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&avail, 0, MAX);

	for(i = 0; i < MAX; i++){					/* 顾一批长工 */
		pthread_create(&tid, NULL, tfn, NULL);
		pthread_detach(tid);
		printf("%u show-up\n", (unsigned)tid);
	}
		
	while(1){									
		sfd = accept(lfd, NULL, NULL);			/* 等待玉米成熟  成熟后，将玉米穗用收割机收割*/
		
		sem_wait(&empty);						/* 等待可用的粮仓, 申请粮仓*/
		cfd = sfd;								/* 将收割机中的玉米穗放入粮仓*/
		sem_post(&full);						/* 开放粮仓大门 ,等待工人进入拨玉米  惊群唤醒所有工人 */

		n = sem_trywait(&avail);				/* 看看长工够不够 */
		if(n == -1){												/*长工不够用，需要雇用短工 */
			if(errno == EAGAIN){
				pthread_create(&tid, NULL, tfn, NULL);
				pthread_detach(tid);
				printf("%u new worker\n", (unsigned)tid);
			}else{							
				printf("error...\n");
				return -1;
			}
		}
	}

	return 0;
}
