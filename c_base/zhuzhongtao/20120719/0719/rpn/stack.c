#include "calc.h"
#define MAXVAL 100
static int sp = 0;
static double val[MAXVAL];
void push(double f) { val[sp++] = f; }
double pop() { return val[--sp]; }
