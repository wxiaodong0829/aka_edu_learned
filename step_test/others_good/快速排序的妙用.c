#include<stdio.h>
#include<string.h>
#include<ctype.h>

char *fun(char * s);//利用快速排序，comp函数定义数字比字母大
int comp(const void *a,const void *b);

int main(void)
{
	char s[] = "asd123fgh543df";
	char *str;
	printf("%s\n", s);

	str = fun(s);
	printf("%s\n", str);

	return 0;
}

char *fun(char * s)
{
	qsort(s, strlen(s), sizeof(char), comp);
	return s;
}

int comp(const void *a,const void *b)
{
	return isalpha(*(char*)b) - isalpha(*(char*)a);
}
