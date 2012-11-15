#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int count = 0;
    char *tmp;
    
    if(argc != 3){
        printf("Invalid para!\n");
        return 0;
    }
    for(tmp = argv[1]; *argv[2] && (tmp = strstr(tmp, argv[2])); tmp += strlen(argv[2]))
        count++;

    printf("count = %d\n", count);
    return 0;
}
