#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stud *link;
struct stud{
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
	link next;
};

double ave(link p)
{
	double ave;
	ave = (p->s[0]+ p->s[1] + p->s[2] + p->s[3])/4;
	printf("%lf\n", ave);
	return ave;
}

void writerec(link p)
{
	if(p == NULL)
	{
		printf("empty");
		return ;
	}
	while(p != NULL)
	{
		printf("%d\t %s\t %d\t %d\t %d\t %d\t %lf\n", p->id, p->name, p->s[0], p->s[1], p->s[2], p->s[3],p->ave);
		p = p->next;
	}
}

link readrec(link head, int n)
{
	int i;
	link p1 = NULL;
	for(i = 0; i < 10; i++)
	{
		link p = (link)malloc(sizeof(*p));
		printf("input student's %d id:", i+1);
		scanf("%hu", &p->id);
		printf("input student's %d name:", i+1);
		scanf("%s", p->name);
		printf("input student's %d 4 score:", i+1);
		scanf("%d", &p->s[0]);
		scanf("%d", &p->s[1]);
		scanf("%d", &p->s[2]);
		scanf("%d", &p->s[3]);

//		printf("%ld\n", (double)((double)p->s[0]+ (double)p->s[1] + (double)p->s[2] + (double)p->s[3])/4);
		p->ave = (p->s[0]+ p->s[1] + p->s[2] + p->s[3])/4;
		//scanf("%d,%d,%d,%d", p->s[0], &p->s[1], &p->s[2], &p->s[3]);
		if(p1 == NULL)
		{
			head = p;
			p1 = head;
		}
		{
			p1->next = p;
			p1 = p;
		}
	}
	p1->next = NULL;

	return head;
}

int main(int argc, char *argv[])
{
	link head;
	head = readrec(head, 10);
	writerec(head);
	free(head);
	return 0;
}
