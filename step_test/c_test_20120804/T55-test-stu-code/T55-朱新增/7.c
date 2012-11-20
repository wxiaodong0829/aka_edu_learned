#include <stdio.h>

struct stud
{
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
};
int main(int argc, char *argv[])
{
	struct stud arr[N];	

	readrec(arr);
	writerec(arr);

	return 0;
}

