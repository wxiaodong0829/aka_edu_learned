#include <stdio.h>
#define N 10
#if 0
void readrec(struct stud *stu)
{
        int i;
        for(i = 0; i < N; i++) 
        {     scanf("%d,%s,%d,%d,%d,%d",\
            &(stu[i]->id), stu[i]->name, &(stu[i]->s[0]),&(stu[i]->s[1]), &(stu[i]->s[2]), &(stu[i]->s[3]));
            
            printf("%d\n",stu[i]->id);
        }

}
#endif
int main(void)
{
    struct stud{
        unsigned short id;
        char name[10];
        int s[4];
        double ave;
    }stu[N];
    
    stu[0]->id=100;
    printf("%d\n", stu[0]->id);
#if 0
    readrec(stu);
    writerec(stu);
#endif
    return 0;


}
