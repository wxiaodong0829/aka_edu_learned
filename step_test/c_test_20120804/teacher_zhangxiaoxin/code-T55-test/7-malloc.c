#include <stdio.h>
#include <stdlib.h>
#define N 2

struct stud
{
	unsigned short id;
	char *pname;
	int s[4];
	double ave;
}*pstd;

void readrec(struct stud *pstd)
{
	int i, j;
	int sum;

	printf("id\tname\ts[1]\ts[2]\ts[3]\ts[4]\tave\n");
	for(i = 0; i < N; i++)
	{
		sum = 0;
		pstd[i].pname = malloc(sizeof(char) * 20);
		scanf("%hu\t%s", &pstd[i].id, pstd[i].pname);		
		for(j = 0; j < 4; j++)
		{
			scanf("\t%d", &pstd[i].s[j]);
			sum += pstd[i].s[j];
		}
		pstd[i].ave = sum / 4;
//		printf("%lf\n", pstd[i].ave);
	}
}

void writerec(struct stud *pstd)
{
	int i, j ;

	printf("id\tname\ts[1]\ts[2]\ts[3]\ts[4]\tave\n");
	for(i = 0; i < N; i++)
	{
		printf("%d\t%s\t", pstd[i].id, pstd[i].pname);
		for(j = 0; j < 4; j++)
		{
			printf("%d\t", pstd[i].s[j]);
		}
		printf("%lf\n", pstd[i].ave);
	}
}

int main(int argc, char *argv[])
{

	pstd = malloc(sizeof(struct stud) * N);
	readrec(pstd);
	writerec(pstd);

	free(pstd);
	return 0;
}


