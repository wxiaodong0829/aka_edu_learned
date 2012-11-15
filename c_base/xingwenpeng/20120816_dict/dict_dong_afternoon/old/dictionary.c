#include <stdio.h>
#include "dictionary.h"
#include "word_default.h"
#include "binary_default.h"


int main(int argc, char *argv[])
{
	
	FILE *fp;
/*	fp = fopen("dat", "rb");
	char buf[BUFSIZ];
	fread(buf, 7, 1, fp);
	printf("%s\n", buf);
	//fwrite("abcdefg", 7, 1, fp);
*/
	bd_binary_default("dict.txt", "dict.dat");
#if 0
	if (argc < 2) {
		printf("Please input a argument \n");
		exit(-1);
	}
	if (argc == 2) {
		if (strcmp(argv[1], "-word") == 0)
			wd_word_default("dict.txt");
//		else if (strcmp(argv[1], "-index") == 0) {
//			bd_binary_default("dict.txt", "dict.dat")
//		}
	}
#endif
	return 0;

}
