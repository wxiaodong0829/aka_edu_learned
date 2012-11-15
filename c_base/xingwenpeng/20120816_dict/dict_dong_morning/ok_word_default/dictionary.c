#include <stdio.h>
#include "dictionary.h"
#include "word_default.h"


int main(int argc, char *argv[])
{
	
	wd_word_default("dict.txt");
#if 0
	if (argc < 2) {
		printf("Please input a argument \n");
		exit(-1);
	}
	if (argc == 2) {
		if (strcmp(argv[1], "-word") == 0)
			word_default("dict.txt");
//		else if (strcmp(argv[1], "-index") == 0) {
//			bin_default("dict.txt", "dict.dat")
//		}
	}
#endif
	return 0;

}
