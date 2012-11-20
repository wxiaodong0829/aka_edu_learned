#include <stdio.h>
#define N 10 
typedef struct stud{
	int id;
	char name[10];
	int s[4];
	double ave;
}stud;
void readrec(stud st[])
{
	int i;
	double tmp;
	for (i=0; i<N; i++) {
		printf("please input:number  name  four grade\n");
		scanf("%d%s%d%d%d%d", &st[i].id, st[i].name, &st[i].s[0], &st[i].s[1], &st[i].s[2], &st[i].s[3]);
		tmp = (st[i].s[0] + st[i].s[1] + st[i].s[2] + st[i].s[3])/4;
		tmp = (st[i].s[0] + st[i].s[1] + st[i].s[2] + st[i].s[3])/4;
		st[i].ave = tmp;
	}
}
void writerec(stud st[])
{
	int i;
	for (i=0; i<N; i++) {
		printf("%d student information is:\n", i+1);	
		printf("id = %d, name = %s, s[0] = %d s[1] = %d s[2] = %d s[3] = %d ,ave = %f", st[i].id, st[i].name, st[i].s[0], st[i].s[1], st[i].s[2], st[i].s[3], st[i].ave);
		printf("\n");
	}
}
int main()
{
	stud s[N];
	readrec(s);
	writerec(s);
}
