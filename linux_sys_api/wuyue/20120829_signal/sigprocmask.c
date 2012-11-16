/*************************************************************************
    > File Name: sigprocmask.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 11时15分16秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

/* ./a.out   ctrl+c ctrl+c  */

int main(void)
{
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, NULL);
	sleep(10);

	sigprocmask(SIG_UNBLOCK, &set, NULL); /* 当解除屏蔽之后，因为pending未决位已经被ctrl+c 设置为1，当时间片结束，就绪队列排到，则开始扫描未决集位图，发现SIGINT对应的位被置1，则检测对应的屏蔽集位图中SIGINT对应的位，现已被置0，即不屏蔽，则执行相应处理方式  */
	while(1);

	return 0;
}
