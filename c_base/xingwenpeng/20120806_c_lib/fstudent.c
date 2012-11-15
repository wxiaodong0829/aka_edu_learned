/*************************************************************************
    > File Name: fstudent.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月06日 星期一 14时08分37秒
 ************************************************************************/

#include <stdio.h>
#define STULEN 4
#define NAMELEN 20
#define MAXLEN 20
union Sex {char man, char women}sex;
typedef struct Stu {
	char name[NAMELEN];
	char id[NAMELEN];
	union sex;
	double core;
} stu;

void mygets(char *s)
{
	int len;
	fgets(s, MAXLEN, stdout);
	len = strlen(s);
	if (s[len - 1] != '\0') {
		s[len - 1] = '\0';
	}
	return;
}
void gets_stu(stu * s)
{
	char buf[DOUBLELEN];
	mygets(s->name);
	mygets(s->id);
	mygets(&(s->sex));
	mygets(buf);
	s->core = atoi(buf);
}
int main(void)
{
	stu s[STULEN];
	int i;
	FILE *fp;
	if ((fp = fopen("out_student", "a+")) == NULL) {
		printf("error open the out_student file");
		exit(-1);
	}

	for (i = 0; i < STULEN; i++) {
		get_stu(&s[i]);
		fwrite(s, sizeof(stu), STULEN, fp);
	}

	return 0;
}
