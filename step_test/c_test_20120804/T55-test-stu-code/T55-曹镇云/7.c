#include<stdio.h>
#define N 2
struct stud{
    unsigned short id;
    char name[10];
    int s[4];
    double ave;
}student[N];

void readrec(struct stud *student)
{
    int i, j, sum=0;
    for(i=0; i<N; i++)
    {
        printf("NO: %d id:", i);
        scanf("%hu", &student[i].id);

        printf("NO: %d name:", i);
        scanf("%s", student[i].name);

        for (j=0; j<4; j++)
        {
            printf("4 scored of %d:", j);
            scanf("%d", &student[i].s[j]);
            sum+=student[i].s[j];
        }
        student[i].ave=sum/4;
        printf("\n");
    }
        printf("\n");

}

void writetec(struct stud *student)
{
    int i, j, sum;
    for(i=0; i<N; i++)
    {
        printf("NO: %d id:", i);
        printf("%hu\n", student[i].id);

        printf("NO: %d name:", i);
        printf("%s\n", student[i].name);

        for (j=0; j<4; j++)
        {
            printf("4 scored of %d:", j);
            printf("%3d\n", student[i].s[j]);
            sum+=student[i].s[j];
        }
        printf("ave :%.2f", student[i].ave);

        printf("\n");
        printf("\n");
    }

}

int main(void)
{
    readrec(student);
    writetec(student);

}
