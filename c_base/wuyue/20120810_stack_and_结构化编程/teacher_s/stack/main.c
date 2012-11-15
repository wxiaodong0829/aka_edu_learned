#include <stdio.h>
#include "stack.h"

int main(void)
{
    int n;

    while(1){
        scanf("%d", &n);
        if(n == -1)
            break;
        push(n);
    }

    while(is_empty() == 0){
        n = pop();
        printf("%d ", n);
    }
    printf("\n");

    return 0;
}
