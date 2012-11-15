/*************************************************************************
    > File Name: fseek.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月06日 星期一 15时06分23秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PUTBUF 4096
/* myfgets 
 * out: char *s, 将要保存到的数组指针
 * 
 * 
 * 
 */ 
char * myfgets(char *s, int size, FILE *fp)
{
	int len;
	if ((s = fgets(s, size, fp)) == NULL) {
		return NULL;
	}
	len = strlen(s);
	if (s[len - 1] == '\n') {
		s[len - 1] = '\0';
	}
	return s;
}
int get_http(char *src, char ** dest)
{
	char *p;
	for (p = src; p = strtok(p, " "); p = NULL) {
		if (strncmp(p, "http", 4) == 0) {
			//printf("token right ?\n");
			*dest = p;
			return 1; //geted 
		}
	}
	return 0; //not get
}

int cmp(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

void get_put(FILE *fpsrc, FILE *fpdest)
{
	char buf[BUFSIZ/10][BUFSIZ];
	char *put_buf[BUFSIZ] = {NULL};
	char *tmp;
	int http_num = 0;
	int i, n;
	
	i = 0;
	while ((tmp = myfgets(buf[i], BUFSIZ, fpsrc)) != NULL) {
		if ((n = get_http(tmp, &(put_buf[i++]))) == 1) {
			http_num++;
		}
	}

	qsort(put_buf, http_num, sizeof(char *), cmp);
	i = 0; 
	//printf("%d\n", http_num);

	while (http_num-- > 0) {
		fputs(put_buf[i++], fpdest);
		fputs("\n", fpdest);
	}
}

int main(int argc, char *argv[])
{
	FILE *fpsrc, *fpdest;
	
	if ((fpsrc = fopen(argv[1], "r+")) == NULL || ((fpdest = fopen("tmp_log", "w+")) == NULL)) {
		printf("error");
		exit(-1);
	}
	get_put(fpsrc, fpdest);

	fclose(fpsrc);
	fclose(fpdest);

	return 0;
}
