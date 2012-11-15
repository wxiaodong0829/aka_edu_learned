#include <stdio.h>
#include <string.h>

int main(void)
{
    char src[] = "http://www.google.cn/search?complete=1&hl=zh-CN&ie=GB2312&q=linux&meat=";
    char *begin, *content, *key, *savep1, *savep2;

    begin = strchr(src, '?') + 1;

    for(; (content = strtok_r(begin, "&", &savep1)); begin = NULL){
        key = strtok_r(content, "=", &savep2);
        printf("key = %s, value = %s\n", key, savep2);
    }
    return 0;
}
