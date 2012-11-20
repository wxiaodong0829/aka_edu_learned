#include <stdio.h>
#include <string.h>

void *cal(void *a, void *b, void (*f)(void *a, void *b))
{
	void *ret;

}

void *add(void *a, void *b)
{
	return *(int *)a + *(int *)b;
}

int main(int argc, char *argv[])
{
	int c;
	int a = 2, b = 3;
	if(argc < 3)
	  return;

	void *(*f)(void *);
	calu((void *)a, (void *)b, add);
	return 0;
}
