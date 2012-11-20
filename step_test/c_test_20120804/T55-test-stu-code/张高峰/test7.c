#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stud *node;
struct stud{
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
}*p[10];

void readrec(unsigned short id,char *name,int *s)
{
	int i=0;
	node t;
	p[i++]=t=malloc(sizeof *t);
	double ave=0;
	while(i<4)
	{
		ave=ave+s[i++];
	}
	ave=ave/4.0;
	t->id=id;
	strcpy(t->name,name);
	for(i=0;i<4;i++)
		t->s[i]=s[i];
	t->ave=ave;
}

void writerec()
{
	int i=0;
	for(;i<10;i++)
	{
		printf("the number %d student message!",i+1);
		printf("student id:%d\n",p[i]->id);
		printf("student name:%s\n",p[i]->name);
		printf("student score:%d %d %d %d\n",p[i]->s[0],p[i]->s[1],p[i]->s[2],p[i]->s[3]);
	printf("student ave:%lf\n",p[i]->ave);
	}
}

int main(void)
{
	unsigned short id;
	int i;
	char name[10];
	int s[4];
	for(i=0;i<10;i++)
	{
		printf("the %d student message!\n",i+1);
		printf("Please input student id:");
		scanf("%d",&id);
		printf("Please input student name:");
		scanf("%s",name);
		printf("Please input student 4 score:");
		scanf("%d %d %d %d",&s[0],&s[1],&s[2],&s[3]);
		readrec(id,name,s);
	}
	writerec();
	return 0;
}
