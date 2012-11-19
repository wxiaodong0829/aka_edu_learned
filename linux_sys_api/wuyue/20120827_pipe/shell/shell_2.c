/*************************************************************************
    > File Name: shell.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月27日 星期一 13时23分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "err.h"
#include "debug.h"

typedef struct arg{
	int argc;
	char **argv;
	char *in;
	char *out;
}arg_t;

int do_parent(int fd[][2], int n_child);
int do_child(char *args, int id_child, int fd[][2], int n_child);

int get_count_args(char *buf)
{
	int flag = 0;
	int i, n;
	int len = 0;
	for (i = 0; buf[i]; i++) {
		if (buf[i] == ' ' && flag == 0) {
			flag = 0;
			continue;
		} else if (buf[i] == ' ' && flag == 1) {
			flag = 0;
			continue;
		} else if (buf[i] != ' ' && flag == 0) {
			flag = 1;
			len++;
			continue;
		}
	}
	return len;
}
int init(arg_t *arg, int *n)
{
		char *args[BUFSIZ];
		char buf[BUFSIZ];
		char input_argv[BUFSIZ];
		char *in; char *p, *q;
		int len; int i, j;
		printf("$ ");
		fflush(stdout);

		if ((in = fgets(input_argv, BUFSIZ, stdin)) == NULL)
			error_user("fgets");
		len = strlen(input_argv);
		if (input_argv[len - 1] == '\n') {
			input_argv[len - 1] = '\0';
			len--;
		}
		if (strcmp(input_argv, "q") == 0) //退出
			return 1;
		// 让用户输入一行命令
		for (i = 0, *n = 0, p = input_argv; (p = strtok(p, "|")) != NULL; p = NULL, i++) {
			len = strlen(p) + 1;
			args[i] = malloc(len);
			strncpy(args[i], p, len - 1);
			(*n)++;
		}
		args[i] = NULL;
		arg = malloc(sizeof(*arg) * (*n));

		for (i = 0; args[i]; i++) {
			for (p = args[i],j = 0; p = strtok(p, "<>"); p = NULL) {
				if (j == 0) {
					len = get_count_args(p);
					arg[i].argv = malloc(sizeof(*argv[i].argv) * len);
					for (q = p, k = 0; q = strtok(q, " "); q = NULL, k++) {
						len = strlen(q) + 1;
						arg[i].argv[k] = malloc(len);
						strncpy(arg[i].argv[k], q, len-1);
					}
				} else if (j == 1) {
					for (q = p; q = strtok(q, " "); q = NULL) {
						len = strlen(q) + 1;
						filename = malloc(len);
					}
				} else
					error_user("usage:cmd  args [<,>] filename\n");
			}
		}
	
}

int  main(void)
{
	char input_argv[BUFSIZ];
	char *in, *p;
	arg_t *args;
	int fd[BUFSIZ][2];

	int i, n, len, ret;
	pid_t pid;
//	printf("%d %d %d\n", get_count_args("ls"), get_count_args("  ls   "), get_count_args("      ls       a                 "));
#if 1
	while (1) {

		if (init(args, &n))
			break;
		//创建n-1个管道
		for (i = 0; i < n-1; i++)
			if ((ret = pipe(fd[i])) == -1)
				error_sys("pipe");
		//创建 n 个子进程	
		for (i = 0; i < n; i++)
			if ((pid = fork()) == 0)
				break;
		if (pid < 0)
			break;
		if (i != n) {
//			if (i == 1)
//				sleep(1);
			do_child(args[i], i, fd, n);
			break;
		}
		else 
			do_parent(fd, n);
//		for (i = 0; i < n; i++)
//			free(args[i]);
	}
#endif
	return 0;
}
int do_parent(int fd[][2], int n_child)
{
	int i;
	for (i = 0; i < n_child - 1; i++) {
				close(fd[i][0]);
				close(fd[i][1]);
	}
	for (i = 0; i < n_child; i++)
		wait(NULL);
	return 0;
}
/*
 * args ：一个进程的命令行参数
 * id_child: 此进程的序号 从 0开始
 * fd：管道描述符数组
 * n_child: 共多少个子进程
 * */
int do_child(char *args, int id_child, int fd[][2], int n_child)
{
	char *two_part[2];
	char *myargv[BUFSIZ/8];
	char *filename;
	int i, len;
	char *tmp;
	int flag_l, flag_r;
	int fd_r, fd_w;

	//判断 < >
	len = strlen(args);
	for (flag_l = 0, flag_r = 0, i = 0; i < len; i++)
		if (args[i] == '<') {
			flag_l = 1;
		} else if (args[i] == '>')
			flag_r = 1;



	for (tmp = args, i = 0; (tmp = strtok(tmp, "<>")) != NULL; tmp = NULL, i++) {
		len = strlen(tmp) + 1; // \0
		two_part[i] = malloc(len);
		strncpy(two_part[i], tmp, len - 1);
	}

	for (tmp = two_part[0], i = 0; (tmp = strtok(tmp, " ")) != NULL; tmp = NULL, i++)
	{
		len = strlen(tmp) + 1;
		myargv[i] = malloc(len);
		strncpy(myargv[i], tmp, len - 1);
	}
	myargv[i] = NULL;

	//获得文件名
	if (flag_l  || flag_r ) {
		for (tmp = two_part[1], i = 0; (tmp = strtok(tmp, " ")) != NULL; tmp = NULL, i++)
		{
			len = strlen(tmp) + 1;
			filename = malloc(len);
			strncpy(filename, tmp, len - 1);
		}
	}


	//对 < > 做出相应操作
	if (flag_l == 1 && id_child == 0) {
		if ((fd_r = open(filename, O_RDONLY)) == -1)
			error_sys("open < ");
		dup2(fd_r, STDIN_FILENO);
		close(fd_r);
	} else if (flag_r == 1 && id_child == n_child-1) {
		if ((fd_w = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			error_sys("open > ");
		dup2(fd_w, STDOUT_FILENO);
		close(fd_w);
	}


	if (id_child == 0 && n_child > 1) {											/* 最左端　*/
		for (i = 1; i < n_child - 1; i++) {
			close(fd[i][0]);
			close(fd[i][1]);
		}
		close(fd[id_child][0]);
		dup2(fd[id_child][1], STDOUT_FILENO);
		close(fd[id_child][1]);
	}
	if (id_child > 0 && n_child > 1 && id_child < n_child - 1) {					/* 中间　*/
		for (i = 0; i < id_child - 1; i++) {
			close(fd[i][0]);
			close(fd[i][1]);
		}
		for (i = id_child + 1; i < n_child - 1; i++) {
			close(fd[i][0]);
			close(fd[i][1]);
		}
		close(fd[id_child - 1][1]);
		dup2(fd[id_child - 1][0], STDIN_FILENO);
		close(fd[id_child - 1][0]);
		 
		close(fd[id_child][0]);
		dup2(fd[id_child][1], STDOUT_FILENO);
		close(fd[id_child][1]);
	}
	if (id_child > 0 && n_child > 1 && id_child == n_child - 1) {					/* 最后　*/
		for (i = 0; i < n_child -2; i++) {
			close(fd[i][0]);
			close(fd[i][1]);
		}
		close(fd[id_child - 1][1]);
		dup2(fd[id_child - 1][0], STDIN_FILENO);
		close(fd[id_child - 1][0]);
	}

		
	execvp(myargv[0], myargv);
	printf("error execvp, may be no found executable");

	return 0;
}
