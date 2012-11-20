#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
double atov(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++);

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}
typedef struct stack_char {
	char *stack;
	int sp;
	int max;
}stack_char;
stack_char *initstack_char(int size)
{
	stack_char * st;
	st=(stack_char *)malloc(sizeof(stack_char));
	st->stack = (char *)malloc(sizeof(char)*size);
	st->max=size-1;
	st->sp=0;
}
int isempty(stack_char *st)
{
	return !(st->sp);
}
int isfull(stack_char *st)
{
	return !(st->sp-st->max);
}
void push(stack_char *st, char c)
{
	if(isfull(st)){
		printf("full stack!");
		return;
	}
	st->stack[st->sp++]=c;
}
char pop(stack_char *st)
{
	if(isempty(st)) {
		printf("empty stack!");
		exit;
	}
	return st->stack[--st->sp];
}
void freestack_char(stack_char * p)
{
	free(p->stack);
	free(p);
}
double S[MAX];
int sp;
void push_(double p)
{
	S[sp++]=p;
}
double pop_()
{
	return S[--sp];
}
int parse(char *buf, char *argv[])
{
	int n=0;
	char * p;
	for (p = buf; p=strtok(p, " \t\n"); p=NULL, n++)
		argv[n]=p;
	argv[n]=p;
	return n;
}
int opc(char c1,char c2)
{
	if (c1=='+'||c1=='-')
		if(c2=='(')
			return 0;
		else return 1;
	else if (c1=='*'||c1=='/')
		if(c2=='('||c2=='+'||c2=='-')
			return 0;
		else return 1;
}
void hzs(char * ss)
{
	int i=0,j=0;
	char c,p;
	char s[100];
	stack_char * op = initstack_char(strlen(ss));
	push(op, '(');
	while((s[i++]=ss[j++])!='\0');
	i=j=0;
	while((c=s[i++])!='\0'&&c!='\n')
		switch (c) {
			case '0' : case '1' : case '2' : case '3' : \
			case '4' : case '5' : case '6' : case '7' : \
			case '8' : case '9' : case ' ' : case '.' : \
								    ss[j++]=c; break;
			case '(' : push(op, c); break;
			case ')' : while((p=pop(op))!='('){ss[j++]=' ';ss[j++]=p;}break;
			case '+' : case '-' : case '*' : case '/' : \
								    while (opc(c, op->stack[op->sp-1])){
									    ss[j++]=' ';
									    ss[j++]=pop(op);
								    }
								    ss[j++]=' ';push(op, c);break;
		}
	while (c=pop(op))
	{
		if(isempty(op))
			break;
		if(c!='('){
			ss[j++]=' ';
			ss[j++]=c;
		}
	}
	freestack_char(op);
	ss[j]='\0';
}
void op(int argc, char **argv)
{
	double n2;
	char c;
	int i;
	sp=0;
	for (i = 0; i < argc; i++) {
		if ((c=argv[i][0])<'0'||c>'9')
			switch(c) {
				case '+':push_(pop_()+pop_());break;
				case '*':push_(pop_()*pop_());break;
				case '/':n2 = pop_();push_(pop_()/n2);break;
				case '-':n2 = pop_();push_(pop_()-n2);break;
			}
		else
			push_(atov(argv[i]));
	}
	printf("%f\n",pop_());
}
void main()
{
	int i, n;
	char str[100];
	char *argv[30];
	while (1){
		scanf("%s", str);
		if (strcmp(str, "#")==0) return;
		hzs(str);
		printf("%s\n", str);
		n = parse(str, argv);
		op(n, argv);
	}
}
