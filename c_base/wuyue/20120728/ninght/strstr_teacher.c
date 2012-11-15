#include <stdio.h>

int main(void)
{
    char buf[] = "aabbbaacd";
    int cur_len, max_len;
    int cur_i, max_i, i;

    cur_i = 0, max_i = 0;
    cur_len = 0, max_len = 0;
    for(i = 0; buf[i] != '\0'; i++){
        if(buf[i] == buf[i + 1])
            cur_len++;
        else{
            cur_len++;
            if(cur_len > max_len){
                max_len = cur_len;
                max_i = cur_i;
            }
            cur_i = i + 1;
            cur_len = 0;
        }
    }

    printf("the max: %dth, ", max_i + 1);
    for(i = 0; i < max_len; i++)
        putchar(buf[max_i + i]);
    putchar('\n');

    return 0;
}
