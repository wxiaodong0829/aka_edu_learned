#include <stdio.h>
#include "stack.h"

int main(void)
{
    node_t tree[7] = {{'A', 1, 2}, {'B', 3,4}, 
        {'C', 5, 6}, {'D', -1,-1}, {'E', -1,-1},
        {'F', -1, -1}, {'G', -1, -1}};
    node_t item;

    push(tree[0]);
    while(is_empty() == 0){
        item = pop();
        putchar(item.ch);
        if(item.r != -1)
            push(tree[item.r]);
        if(item.l != -1)
            push(tree[item.l]);
    }    
    putchar('\n');

    return 0;
}
