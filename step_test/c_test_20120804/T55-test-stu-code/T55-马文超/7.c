#include <stdio.h>
#define N 10
struct stud{
    unsigned short id;
    char name[10];
    int s[4];
    double ave;
};
void readrec(struct stud *stu)
{
   int i, j; 
    printf("id\t\tname \t\ts[4]\t\t\t ave:");
    for (i = 0; i < N; i++)
	printf("%hu %s %lf\n", stu.id, stu.name, stu.ave);
    for (j = 0; j < 4; j++)
	printf("%d\t", stu.s[j]);

}
void writerec(struct stud *stu)
{
    int i, j;
    int sum = 0;
    printf("id\t\tname \t\ts[4]\t\t\t:");
    for (i = 0; i < N; i++)
	scanf("%hu\t %s", &stu.id, &stu.name);
    for (j = 0; j < 4; j++)
    {	scanf("%d\t", &stu.s[j]);
    sum += stu.s[j];
    }
    ave = sum /4;
}
int main(void)
{
    struct stud stu[N];
    writerec(stu);
    readrec(stu);

return 0;
}    
