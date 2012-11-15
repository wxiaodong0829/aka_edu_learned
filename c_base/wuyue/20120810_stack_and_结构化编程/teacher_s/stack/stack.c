#include "stack.h"

static mytype_t stack[512];
static int top = -1;

void push(mytype_t i)
{
    top++;
    stack[top] = i;
}

mytype_t pop(void)
{
    return stack[top--];
}

int is_empty(void)
{
    return top == -1;
}
