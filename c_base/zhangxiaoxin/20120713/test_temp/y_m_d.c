/*************************************************************************
    > File Name: y_m_d.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月13日 星期五 17时26分11秒
 ************************************************************************/

#include<stdio.h>


int main(int argc, char *argv[])
{
	int year, month, day;

	printf("Enter a date(mm/dd/yyy):");
	scanf("%d/%d/%d", &month, &day, &year);
	printf("You enterd the date:%4d/%02d/%02d\n", year, month, day);

	return 0;
}
