#include <stdio.h>
#define N 10
typedef struct stud{
        unsigned short id;
        char name[10];
        int s[4];
        double ave;
} s;

void readrec(s n[])
{
    int i, j;
    for (i=0; i<N; i++) {
        printf("id:");
        scanf("%hd", &n[i].id);
        printf("\nname:");
        scanf("%s", n[i].name);
        printf("\ns:");
        for (j=0; j<4; j++)
            scanf("%d", &n[i].s[j]);
        n[i].ave = (double)(n[i].s[0]+n[i].s[1]+n[i].s[2]+n[i].s[3])/4;
    }

}

void writerec(s n[])
{
    int i, j;
    for (i=0; i<N; i++) {
        printf("id: %hd\n", n[i].id);
        printf("name: %s\n", n[i].name);
        printf("s:");
        for (j=0; j<4; j++)
            printf("%5d", n[i].s[j]);
        printf("\nave: %6.2f", n[i].ave);
        printf("\n\n\n");

    }
}
int main(void)
{
    s st[N];
    readrec(st);
    writerec(st);
    return 0;
}
