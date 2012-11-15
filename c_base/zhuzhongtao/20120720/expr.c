#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 100

static int sp = 0;
double val[MAXVAL];

void push(double f) { val[sp++] = f; }
double pop() { return val[--sp] ; }

int main(int argc, char *argv[])
{
    int i = 0;
    double op2;
	
    while (argv[++i]) {
        switch (argv[i][0]) {
            case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
                push(argv[i][0] - '0'); break;
            case '+':
                push(pop()+pop()); break;
            case '*':
                push(pop()*pop()); break;
            case '-':
                op2 = pop(); push(pop()-op2); break;
            case '/':
                op2 = pop(); push(pop()/op2); break;
            default:
				break;
        }
    }
	printf("\t%.8f\n", pop());  
    return 0;
}
