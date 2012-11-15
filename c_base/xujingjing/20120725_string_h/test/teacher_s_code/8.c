#include <stdio.h>
#include <string.h>
#include <strings.h>

int main(void)
{
    char *strp[] = {"hello world", "hello hell", "hello aka", "hello hello hoho"};
    char *p, substr[20];
    int i, len;
    len = sizeof(strp) / sizeof(strp[0]);

    while(1){
        printf("Input subsrc:");
        scanf("%s", substr);
        if(strcasecmp(substr, "exit") == 0)
            break;
        for(i = 0; i < len; i++){
            p = strp[i];
            while((p = strstr(p, substr))){
                printf("in \"%s\" row:%d, col:%d!\n", strp[i], i + 1, p - strp[i] + 1);
                p += strlen(substr);
            }
        }
        printf("over...\n");
    }
    return 0;
}
