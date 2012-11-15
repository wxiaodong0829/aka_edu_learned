#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int charcmp(const void *ai, const void *aj)
{
    return *(char*)ai - *(char*)aj;
}
#define MAXWORD 100
int main()
{
    char word[MAXWORD], sig[MAXWORD];
    while (scanf("%s", word) != EOF) {
        strcpy(sig, word);
        qsort(sig, strlen(sig), sizeof(char), charcmp);
        printf("%s %s\n", sig, word);
    }
    return 0;
}
