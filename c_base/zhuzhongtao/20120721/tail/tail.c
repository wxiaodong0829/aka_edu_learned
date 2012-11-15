/*************************************************************************
    > File Name: tail.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月21日 星期六 16时09分46秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 1024*10
#define MAXLINE 512
#define min(a, b)  ( ((a) > (b)) ? (b) : (a) )
char buf[MAXBUF + MAXLINE] = {0};
char *f = buf;//依次取出buf中的字符串
char *r = buf;//存进buf中的首地址

void put(char *s)
{
	int len = strlen(s);
	//第一次时 *r  为 '0' 之后的循环中 的判断能否放得下的条件 strlen(r) > len
	if (*r == '\0' || strlen(r) > len) strcpy(r, s);
	else printf("error	: I can't put this string, because the point isn't enough longer.");
	r += len + 1;
	//判断是否到 buf 结尾
	if (r >= buf + MAXBUF) r = buf;
}
char *get()
{
	char *p = f;
	f += strlen(p) + 1;
	if (f >= buf + MAXBUF)
		f = buf;
	return p;
}
int main(int argc, char *argv[])
{
	char line[MAXLINE];	
	int i = 0;
	int nlines = 0;
	int ntail = 0;
	if (argc>1) {
			if (argv[1][0]=='-') ntail = atoi(argv[1]+1);
			if (ntail < 1) ntail = 10;
	}
	while ((scanf("%s", line))!=EOF){
		//nlines++;
		put(line);
		if (++nlines > ntail)	get();
	}
	for (i = 0; i < min(nlines, ntail); i++)
		printf("%s\n", get());

	return 0;
}
