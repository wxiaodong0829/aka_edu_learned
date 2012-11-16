/*************************************************************************
    > File Name: ls_wc.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月27日 星期一 10时33分13秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
	int fd[2];
	pid_t pid;
	int n, i;

	i = pipe(fd);

	for (i = 0; i < 2; i++)
		if ((pid = fork()) == 0)
			break;

	//if (pid < 0)
	//	exit(1);

	if (i == 0) { /* child 1 */
		char *myargv[] = {"ls", NULL};
		//close(0);
		//close(1);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		execvp("ls", myargv);				/* ls  输出到标准输出 */

	} else if (i == 1) { /* child 2 */
		char *myargv[] = {"wc", "-l", NULL};
		int n;
		//close(0);
		//close(1);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		execvp("wc", myargv);			/* wc 从标准输入读取数据 */

	} else if (i == 2) { /* parent */
	//	close(fd[0]);
	//	close(fd[1]);

		for (n = 0; n < i; n++)
			wait(NULL);
	}
}
