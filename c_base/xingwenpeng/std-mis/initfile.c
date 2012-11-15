#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "common.h"

FILE *openfile(char *name, int flag)
{
	FILE *fp = NULL;
	switch(flag)
	{
		case 1: fp = fopen(name, "r");
				break;
		case 4: fp = fopen(name, "w");
				break;
		default: return NULL;
	}
	if(!fp)
	{
		fprintf(stderr, "open %s failed:%s\n", name, strerror(errno));
		return NULL;
	}
	else
		return fp;
}

void closefile(FILE *fp)
{
	fclose(fp);
}
