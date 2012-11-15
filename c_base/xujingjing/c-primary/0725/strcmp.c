#include <stdio.h>
#include <strings.h>

int main(int argc, char **argv)
{
    int i;
    printf("argc = %d\n", argc);
    if(argc != 3){
        printf("Invalid para!\n");
        return 0;
    }
    for(i = 0; i < argc; i++)
        printf("argv[%d]:%p, %s\n", i, argv[i], argv[i]);
    printf("strcasecmp:%d\n", strcasecmp(argv[1], argv[2]));
    return 0;
}
