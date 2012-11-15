#ifndef STACK_H_
#define STACK_H_

typedef struct
{
    char ch;
    int l, r;
}node_t;

typedef node_t mytype_t;

void push(mytype_t i);
mytype_t pop(void);
int is_empty(void);

#endif
