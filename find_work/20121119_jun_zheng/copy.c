#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef unsigned char  uint8_t;
const uint8_t *decode(const uint8_t *src, int *dst_length, int *consumed, int length)
{
	int i, si, di;
	uint8_t *dst;

	si = di = 0;
	while (si+2 < length) {
		if(src[si+2] > 3) {
			dst[di++] = src[si++];
			dst[di++] = src[si++];
		}else if(src[si]==0 && src[si+1]==0) {
			if (src[si+2]==3) {
				dst[di++] = 0;
				dst[di++] = 0;
				si += 3;
				continue;
			}else //next start code
				goto nsc;
		}
		dst[di++] = src[si++];
	}
	while (si < length)
		dst[di++] = src[si++];
nsc:
	memset(dst+di, 0, 8);
	*dst_length = di;
	*consumed = si;
	return dst;
}
int main(void)
{
	uint8_t src[10] = {1, 2, 3, 4, 5};
	uint8_t dst[10] = {0};
	uint8_t *d;
	int dst_length = 5;
	int consumed = 5;
	int length = 5;
	int i;

	d = decode(src, &dst_length, &consumed, length);
	
	for (i = 0; i < 10; i++)
		printf("d[%d] = %d\n", i, d[i]);

	return 0;
}
