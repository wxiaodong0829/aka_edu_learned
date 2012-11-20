#include <stdio.h>
#include <string.h>
#define N 20
void dollars(char *dest, char const *src)
{
	int i, j, s, len = strlen(src), k;
	if (len>5) {
		s = (len-5)%3;
		if (s==1) {
			k = 1;
			j = 0;
			for (i=0; i<len; i++, j++) {
				*(dest + j) = *(src +i);
				if (((len-5)/3+1)--) {
					j = j+k;
					*(dest + j) = ',';
				}
			}
		} else if (s==2) {
			k = 2;
			j = 0;
			for (i=0; i<len; i++, j++) {
				*(dest + j) = *(src +i);
				if (((len-5)/3+1)--) {
					j = j+k;
					*(dest + j) = ',';
				}

		} else if (s==0) {
			k = 0;
			j = 0;
			for (i=0; i<len; i++, j++) {
				*(dest + j) = *(src +i);
				if (((len-5)/3+1)--) {
					j = j+k;
					*(dest + j) = ',';
				}
			
		}
	}
}
int main()
{
	char src[] = "123456";
	char dest[N];
	dollars(dest, src);
	printf("input\toutput\n");
	printf("%s\t%s\n", src, dest);
	return 0;
}
