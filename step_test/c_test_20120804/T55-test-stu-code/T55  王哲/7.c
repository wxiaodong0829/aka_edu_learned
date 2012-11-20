#include <stdio.h>
struct stud {
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
}stu[10];
void reader(struct stud stu[], int n)
{
	int i, j;
	printf("id + name");
	for(i=0;i<5;i++)
	scanf("%d %s",&(stu.id), (stu.name));
	printf("4:");
	for(i=0; i<4; i++)
		scanf("%d",stu.s[i]);
	for(j=0; j<10; j++)
		stu[j].ave = avg1(stu[i], 4);
		

}
float avg1(int s[], int n)
{
	int i, j;
	j = 0;
	float avg1;
	for(i=0; i<n; i++)
		j = j + s[i];
	avg1 =(float)(j/n);
	return avg1;
}
void write(struct stud stu[])
{
	int j;a
	printf("%d %s avg:%2f\n", (stu.id), (stu.name), (stu.ave));
	for(j=0; j<4; j++)
		printf("%d",stu.s[j]);
}
int main()
{
	int i;
	struct stud stu[10];
	
	reader(stu, 10);

	for(i=0;i<10;i++){
		write(stu[i]);
	}
	return 0;
}

