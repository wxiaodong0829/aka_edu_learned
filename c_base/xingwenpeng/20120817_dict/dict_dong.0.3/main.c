/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月16日 星期四 16时32分42秒
 ************************************************************************/
#include "dict.h"
#include "word_default.h"
#include "word_user.h"
#include "binary_default.h"
#include "binary_user.h"
#include "debug.h"


int main(int argc, char *argv[])
{
	char *ret;

	switch(argc) {
		case 2: //
			if (strcmp(argv[1], "-test1") == 0) {
				ret = word_default();
			} else if (strcmp(argv[1], "-test2") == 0){
				ret = binary_default();
			} else {
				printf("please input right args\n");
				return -1;
			}
			break;
		case 4:
			if (strcmp(argv[1], "-test1") == 0) {
				ret = word_user(argv[3]);

			} else if (strcmp(argv[1], "-test2") == 0){
				ret = binary_user(argv[3]);
			} else {
				printf("please input right args\n");
				return -1;
			}
			break;
		default :
				printf("Please input right args\n");
				printf("Example:\n");
				printf("$ ./a.out -test1\n");
				printf("$ ./a.out -test2\n");
				printf("$ ./a.out -test1 -f dict_new.txt\n");
				printf("$ ./a.out -test2 -f dict_new.dat\n");
				return -1;
	}

	if (ret == (char *) 1) {
		puts("Think you enjoy it!");
	} else if (ret == (char *) 2) {
		puts("error!!!");
		exit(-1);
	}

	return 0;
}
