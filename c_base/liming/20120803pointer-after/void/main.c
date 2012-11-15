/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月03日 星期五 15时28分46秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int int_cmp(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}
int double_cmp(void *a, void *b)
{
	return *(double *)a - *(double *)b;
}
int str_cmp(void *a, void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}
void * max(void *buf, int len, size_t size, int (*cmp)(void *a, void *b))
{
	void *ret = NULL;
	int i;
	int cm = 0;

	ret = buf;
	for (i = 0; i < len; i++) {
		if ((cm = cmp(ret,(char *)buf + sizeof(size)*(i))) < 0)
			ret = ((char *)buf + sizeof(size)*i);
	}
	return ret;
}

char *s[10] = {"abc", "defg", "ddd", "zhang"};

int main(void)
{
	int i, len;
	int n[5] = {8, 2, 3, 11, 15};
	double d[10] = {3.3, 3.5, 6.0, 10};

	void *ret; 
	ret = max(n, sizeof(n)/sizeof(n[0]), sizeof(n[0]), int_cmp);
	printf("int max = %d\n\n", *(int *)ret);

	ret = max(d, sizeof(d)/sizeof(d[0]), sizeof(d[0]), double_cmp);
	printf("double max = %f\n\n", *(double *)ret);

	for (i = 0, len = 0; s[i]; i++)
		len++;
	ret = max(s, len, sizeof(s[0]), str_cmp); //充分体现了传指针的优势--> 更易于对齐
	printf("str max = %s\n", *(char **)ret);


	return 0;
}
