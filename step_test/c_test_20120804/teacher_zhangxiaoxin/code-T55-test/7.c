#include <stdio.h>
#define N 2

struct stud
{
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
};

void readrec(struct stud *arr)
{
	int i, j;
	int sum;

	printf("id\tname\ts[1]\ts[2]\ts[3]\ts[4]\tave\n");
	for(i = 0; i < N; i++)
	{
		sum = 0;
		scanf("%hu\t%s", &arr[i].id, arr[i].name);		
		for(j = 0; j < 4; j++)
		{
			scanf("\t%d", &arr[i].s[j]);
			sum += arr[i].s[j];
		}
		arr[i].ave = sum / 4;
//		printf("%lf\n", arr[i].ave);
	}
}

void writerec(struct stud *arr)
{
	int i, j ;

	printf("id\tname\ts[1]\ts[2]\ts[3]\ts[4]\tave\n");
	for(i = 0; i < N; i++)
	{
		printf("%d\t%s\t", arr[i].id, arr[i].name);
		for(j = 0; j < 4; j++)
		{
			printf("%d\t", arr[i].s[j]);
		}
		printf("%lf\n", arr[i].ave);
	}
}

int main(int argc, char *argv[])
{
	struct stud arr[N];	

	readrec(arr);
	writerec(arr);

	return 0;
}


