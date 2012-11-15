#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int i, j;

    if(argc != 2){
        printf("Invalid para!\n");
        return 0;
    }
    for(i = 0, j = strlen(argv[1]) - 1; i <= j; i++, j--)
        if(argv[1][i] != argv[1][j])
            break;

    if(i <= j)
        printf("Not palindrom!\n");
    else
        printf("Palindrom!\n");
    return 0;
}

