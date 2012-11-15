/*************************************************************************
    > File Name: switch_grade.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 18时11分24秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, const char *argv[])
{
	int grade;


	while(1)
	{
		printf("Please enter grade(0-4): ");
			scanf("%d", &grade);
			printf("   %d ", grade);
			sleep(2);

		switch(grade)
		{
			case 4:
				printf("Excellent\n");
				break;
			case 3:
				printf("Good\n");
				break;
			case 2:
				printf("Averge\n");
				break;
			case 1:
				printf("Poor\n");
				break;
			case 0:
				printf("Failing\n");
				break;
			default:
				printf("llldgal grade\n");
				break;

		}

		if((grade < 0) || (grade > 4))
			break;

	}
	return 0;
}
