1, strncpy(char *dest, char *src, int n)
	dest[100] 必须初始化 ，否则不一定正确
2,#include <string.h>

       void *memcpy(void *dest, const void *src, size_t n);
		size_t n 以字节为单位
3, #include <string.h>

       int memcmp(const void *s1, const void *s2, size_t n);
		size_t n 以字节为单位

