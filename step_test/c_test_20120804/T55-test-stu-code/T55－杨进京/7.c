#include <stdio.h>

struct stud
{
        unsigned short id;
        char name[10];
        int s[4];
        double ave;
};

void readrec()
{
        
}
int main()
{
    struct stud stu[10];
    
    readrec(stu);

        return 0;
}
