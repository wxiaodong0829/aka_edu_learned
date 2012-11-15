#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100
int main()
{
    char word[MAXWORD], sig[MAXWORD], oldsig[MAXWORD];
    int linenum = 0;
    strcpy(oldsig, "");
    while (scanf("%s %s", sig, word) != EOF) {
        if (strcmp(oldsig, sig) != 0 && linenum > 0)
            printf("\n");
        strcpy(oldsig, sig);
        linenum++;
        printf("%s ", word);
    }
    printf("\n");
    return 0;
}
