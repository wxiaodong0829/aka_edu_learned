/*************************************************************************
    > File Name: 7_struct.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 13时56分21秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define STULEN 10
struct stud {
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
};
typedef struct stud stu;


int getword(char *, int);

void readrec(stu *pt,int len)
{
	int i;
	for (i = 0; i < len; i++) {
		printf("%hu  ", pt[i].id);
		printf("%s   ", pt[i].name);
		printf("%d   ", pt[i].s[0]);
		printf("%d   ", pt[i].s[1]);
		printf("%d   ", pt[i].s[2]);
		printf("%d   ", pt[i].s[3]);
		printf("%3.1f\n", pt[i].ave);
	}
}
void writerec(stu *pt, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		scanf("%u", &pt[i].id);
		scanf("%s", pt[i].name);
		scanf("%d", &pt[i].s[0]);
		scanf("%d", &pt[i].s[1]);
		scanf("%d", &pt[i].s[2]);
		scanf("%d", &pt[i].s[3]);
		pt[i].ave = (double)(pt[i].s[0] + pt[i].s[1] + pt[i].s[2] + pt[i].s[3])/4.0;
	}
}
int main(void)
{
	stu st[STULEN];
//	printf("%d\n", sizeof(st));
	writerec(st, sizeof(st)/sizeof(st[0]));
	readrec(st, sizeof(st)/sizeof(st[0]));

	return 0;
}
