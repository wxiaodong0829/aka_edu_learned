/*************************************************************************
    > File Name: my_cp.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月06日 星期一 10时27分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fpsrc;
	FILE *fpdest;
	int ret;
	char tmp;
	int len;

	if (argc < 3) {
		printf("error is my_cp need two filename\n");
		exit(-1);
	}
	if (((fpsrc = fopen(argv[2], "r")) == NULL) || ((fpdest = fopen(argv[1], "w")) == NULL)) {
		printf("open is error \n");
		exit(-1);
	}
	
	while ((len = fread(&tmp, 1, 1, fpsrc)) != 0)
		fwrite(&tmp, 1, len, fpdest);
	if ((ret = fclose(fpsrc)) == EOF || (ret = fclose(fpdest)) == EOF) {
		printf("error is that can't close file");
		exit(-1);
	}
	return ret;
}
