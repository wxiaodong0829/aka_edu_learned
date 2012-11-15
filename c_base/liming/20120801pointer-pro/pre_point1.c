/*************************************************************************
    > File Name: pre_point.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月01日 星期三 09时10分34秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define DONE 0
#define GOOD 1
#define WELL 0

#if DONE
int parse(char * buf, char * argv[])
{
	int argc;
	int i;
	int j;
	int len = 0;
	for (i = 0, j = 0; buf[i]; i++) {
		if (buf[i] == ' ' && buf[i+1] != ' ' && buf[i+1] != '\0') {
			argv[j++] = &buf[i+1];
		} else if (buf[i] == ' ' && buf[i-1] != ' ') {
			buf[i] = '\0';
		}
	}
	return argc = j;
}
#endif

#if GOOD
int parse(char *buf, char * argv[])
{
	int argc = 0;
	char *p = NULL;

	for (p = buf; p = strtok(p, " "); p = NULL) {
		argv[argc++] = p;
	}
	argv[argc] = NULL;
	return argc;
}
#endif

#if WELL
int parse(char * buf, char * argv[])
{
	int argc = 0;
	int flag;
	int i, j;
	flag = 0;// ' '
	for (i = 0, j = 0, flag = 0; buf[i]; i++) {
		if (buf[i] == ' ' && flag == 1) {
			flag = 0;

			buf[i] = '\0';
		} else if (buf[i] != ' ' && flag == 0) {
			flag = 1;

			argv[j++] = &buf[i];
			argc++;
		}
	}
	argv[j] = NULL;
	return argc;
}
#endif

int main(void)
{
	int i;
	char buf[32] = "  ./a.out 123  567  9";
	int argc;
	char *argv[10];
	
	argc = parse(buf, argv);

	//for (i = 0; i < argc; i++) 
	for (i = 0; argv[i]; i++) 
		printf("argv[%d] = <%s>\n", i, argv[i]);
	


	return 0;
}
