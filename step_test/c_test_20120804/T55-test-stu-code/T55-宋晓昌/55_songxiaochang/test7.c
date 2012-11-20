#include<stdio.h>
struct stu
{
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
};
void readrec(struct stu )
{
		struct stu student;
		student.id=1;
		student.name[0]='s';
		student.s[0]=90;
}
int main(void)
{
	struct stu std;
	readrec(std);
	printf("%d\n",std.id);
	return 0;
}
