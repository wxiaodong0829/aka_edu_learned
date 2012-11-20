/*
 * =====================================================================================
 *
 *       Filename:  5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月04日 16时00分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
struct stud{
	int id;
	char name[10];
	int s[4];
	float ave;
};
void readrec(struct stud *p)
{
	int i;
	printf("id name s[0] s[1] s[2] s[3]\n");
	for(i=0; i<10; i++)
	{
		scanf("%d %s %d %d %d %d", &p[i].id, p[i].name, &p[i].s[0], &p[i].s[1], &p[i].s[2], &p[i].s[3]);
		p[i].ave = (p[i].s[0]+p[i].s[1]+p[i].s[2]+p[i].s[3])/4;
	}
}
void writerec(struct stud *p)
{
	int i;
	for(i=0; i<10; i++)
	printf("%d %s %d %d %d %d %f\n", p[i].id, p[i].name, p[i].s[0], p[i].s[1], p[i].s[2], p[i].s[3], p[i].ave);
}
int main()
{
	struct stud stu[10];
	readrec(stu);
	writerec(stu);
	return 0;
}
