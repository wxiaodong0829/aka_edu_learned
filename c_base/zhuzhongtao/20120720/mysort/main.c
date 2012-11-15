/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月20日 星期五 19时23分43秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		/*	进行排序的最大文本行数	*/

char *lineptr[MAXLINES];	/*	指向文本的指针数组		*/

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nline);

void qsort(char *lineptr[], int left, int right);
/*	对输入的文本行进行排序	*/
int main(void)
{
	int nlines;		/*	读取的输入行数目	*/

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
