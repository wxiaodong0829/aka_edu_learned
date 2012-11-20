#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void dollars(char *dest,char const *src)
{
   int i;
   int k=0;
    int j=1;
   for(i=0;src[i];i++);
	dest[0] ='$';
	for(j;j<i;j++,k++)
	{
		dest[j]=src[k];
	}
	for()
}
int main(void)
{
	char src[100];
	scanf("%s",src);
	dollars();

	return 0;
}

