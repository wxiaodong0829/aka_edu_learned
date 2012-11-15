#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ITERM_SIZE	4
int len  = 10;
int *num_malloc(int num)
{
	int *p = (int *)malloc(sizeof(int));
	if (p == NULL) {
		perror("malloc");
		return NULL;
	}
	*p = num;
	return p;
}
int *arry_malloc(int *ptr, int size)
{
	int *p = NULL;
	p = realloc(ptr, size);
	if(p == NULL) {
		perror("realloc");
		return NULL;
	}
	return p;
}
int main(void)
{
	int *addr = NULL;
	int *arry_addr = NULL;
	int num, i = 0, j;
	char buf[100];
	int tmp_len;
	
	printf("Please input num:");
	arry_addr = arry_malloc(NULL, len * ITERM_SIZE);
	if (arry_addr == NULL) {
		printf("arry_malloc fail\n");
		exit(-1);
	}
	while(1) {
		fgets(buf, sizeof(buf), stdin);
		tmp_len = strlen(buf);
		buf[tmp_len-1] = '\0';
		num = atoi(buf);
		if (num == 0)
			break;
		addr = num_malloc(num);
		if (addr == NULL) {
			printf("num_malloc fail\n");
			exit(-1);
		}
		if (i == len) {
			len += 10;
			arry_addr = arry_malloc(arry_addr, len * ITERM_SIZE);
		}
		*(arry_addr+i) =  (int)addr;
		i++;
	}	

	for (j = 0; j < i; j++) {
		printf("%d", **(int **)(arry_addr+j));
		free(*(arry_addr+j));
	}

	puts("\n");
	free(arry_addr);
	return 0;
	

}
