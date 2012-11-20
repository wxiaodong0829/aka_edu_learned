#include <stdio.h> 
struct stud{
	int id;
	char name[5];
	int s[2];
	float ave;
}stu[5];

float aver(int s[], int n)
{
	int i, sum = 0;
	float average;
	for (i = 0; i < n; i++)
		sum += s[i];
	average =(float )(sum / n);
	return average;
}
void readrec(struct stud stu[], int n)
{
	int i, j;
	printf("Please input the  id and name: \n");
	for(i = 0; i < 5; i++)
		scanf("%d %s", &(stu[i].id), (stu[i].name));

	printf("Please input the student's score:\n");
	for(i = 0; i < 5; i++)
	{
		printf("score of (%s) : ", stu[i].name);
		for(j = 0; j < 2; j++)
			scanf("%d", &(stu[i].s[j]));
	}
	for(i = 0; i < 5; i++)
		stu[i].ave = aver(stu[i].s, 2);
	/*	for(i = 0; i < 5; i++)
		{
		printf("ave score of (%s) is : ", stu[i].name);
		printf("%.2f\n", stu[i].ave);
		}
		*/
}

void writerec(struct stud stu)
{ 
	int j;
	printf("%d_%s :average score %.2f\n", stu.id, stu.name, stu.ave);
	printf("-> score is :");
	for(j = 0; j < 2; j++)
		printf("%d ", stu.s[j]);
	printf("\n");

}
int main()
{
	int i;
	struct stud stu[5];
	readrec(stu, 5);
	for(i = 0; i< 5; i++)
		writerec(stu[i]);

	return 0;


}
