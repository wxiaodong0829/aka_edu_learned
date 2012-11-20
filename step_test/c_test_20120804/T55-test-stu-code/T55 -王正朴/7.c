#include <stdio.h>
struct stud
{
	unsigned shrot id;
	char name[10];
	int s[4];
	double ave;
};

void readrec(struct stud stu[])
{
	int i,j,sum =0;
	for (i = 0; i < 10; i++)
	{
		printf("enter the id:");
		scanf("%d",&stu[i].id);
		printf("enter the name:");
		scanf("%s",stu[i].name);
		for(j =0; j < 4; j++)
		{
			printf("enter the  student's score :");
			scanf("%d",&stu[i].s[j]);
			sum += stu[i].s[j];
		}
		stu[i].ave =sum/4;
		sum =0;
	}
}
void writerec(struct stud stu[])
{
	int i,j;
	for(i =0; i <10; i++)
	{
		printf("%d",stu[i].id);
	printf("%d",stu[i].name);
	for(j =0; j <4; j++)
		printf("the %d student's score :%d\n",j + 1,stu[i].s[j]);
	printf("%f",stu[i].ave);
	}
}
int main ()
{
	struct  stud stu[10];
	readrec(stu);
	writerec(stu);

	return 0;
}
