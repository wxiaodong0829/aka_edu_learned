#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20090221

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
#ifdef YYPARSE_PARAM_TYPE
#define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
#else
#define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
#endif
#else
#define YYPARSE_DECL() yyparse(void)
#endif /* YYPARSE_PARAM */

extern int YYPARSE_DECL();

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "egrep.y"
/*===========================================================================
 Copyright (c) 1998-2000, The Santa Cruz Operation 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 *Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

 *Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 *Neither name of The Santa Cruz Operation nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission. 

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 DAMAGE. 
 =========================================================================*/

/* $Id: egrep.y,v 1.11 2006/04/21 10:45:48 broeker Exp $ */

/*
 * egrep -- fine lines containing a regular expression
 */
#line 48 "egrep.y"
#include "global.h"
#include <ctype.h>
#include <stdio.h>

#include <setjmp.h>	/* jmp_buf */

#define nextch()	(*input++)

#define MAXLIN 350
#define MAXPOS 4000
#define NCHARS 256
#define NSTATES 128
#define FINAL -1
static	char gotofn[NSTATES][NCHARS];
static	int state[NSTATES];
static	char out[NSTATES];
static	unsigned int line;
static	int name[MAXLIN];
static	unsigned int left[MAXLIN];
static	unsigned int right[MAXLIN];
static	unsigned int parent[MAXLIN];
static	int foll[MAXLIN];
static	int positions[MAXPOS];
static	char chars[MAXLIN];
static	int nxtpos;
static	int nxtchar;
static	int tmpstat[MAXLIN];
static	int initstat[MAXLIN];
static	int xstate;
static	int count;
static	int icount;
static	char *input;
static	long lnum;
static	int iflag;
static	jmp_buf	env;	/* setjmp/longjmp buffer */
static	char *message;	/* error message */

/* Internal prototypes: */
static	void cfoll(int v);
static	void cgotofn(void);
static	int cstate(int v);
static	int member(int symb, int set, int torf);
static	int notin(int n);
static	void synerror(void);
static	void overflo(void);
static	void add(int *array, int n);
static	void follow(unsigned int v);
static	int unary(int x, int d);
static	int node(int x, int l, int r);
static	unsigned int cclenter(int x);
static	unsigned int enter(int x);

static int yylex(void);
static int yyerror(char *);
#line 127 "egrep.c"
#define CHAR 257
#define DOT 258
#define CCL 259
#define NCCL 260
#define OR 261
#define CAT 262
#define STAR 263
#define PLUS 264
#define QUEST 265
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    1,    1,    2,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,
};
static const short yylen[] = {                            2,
    1,    2,    4,    3,    3,    0,    1,    1,    1,    1,
    3,    2,    2,    2,    2,    3,    1,
};
static const short yydefred[] = {                         0,
    6,    0,    1,    0,    0,   17,    7,    8,    9,   10,
    0,    0,    0,    0,    0,   13,   14,   15,    0,    0,
    0,   16,    0,
};
static const short yydgoto[] = {                          2,
    3,    4,   19,
};
static const short yysindex[] = {                      -261,
    0,    0,    0,   -7,   -7,    0,    0,    0,    0,    0,
   -7,  -27,  -17,  -37,   -7,    0,    0,    0, -236,   -7,
   -7,    0,    8,
};
static const short yyrindex[] = {                        18,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    5,    6,    0,    7,    0,    0,    0,    1,   10,
    0,    0,    2,
};
static const short yygindex[] = {                         0,
    0,   11,    4,
};
#define YYTABLESIZE 278
static const short yytable[] = {                          1,
   12,   11,   11,   22,    2,    4,    5,   12,   13,    3,
    0,    5,   11,    0,   14,    0,    0,    0,   23,    6,
    0,    0,   11,   23,   23,    0,   16,   17,   18,    0,
    0,    0,   11,    0,    0,    0,    0,    0,    0,    0,
   12,   12,   11,    0,    0,    0,    0,   11,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    6,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    6,    7,
    8,    9,   10,   21,    0,   16,   17,   18,    6,    7,
    8,    9,   10,   15,    0,   16,   17,   18,    6,    7,
    8,    9,   10,   20,    0,   16,   17,   18,    6,    7,
    8,    9,   10,    0,    0,    0,    0,   12,   12,   12,
   12,   12,   11,    6,    7,    8,    9,   10,    0,    0,
   16,   17,   18,    6,    6,    6,    6,    6,
};
static const short yycheck[] = {                        261,
    0,    0,   40,   41,    0,    0,    0,    4,    5,    0,
   -1,    1,   40,   -1,   11,   -1,   -1,   -1,   15,  256,
   -1,   -1,   40,   20,   21,   -1,  263,  264,  265,   -1,
   -1,   -1,   40,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   40,   41,   41,   -1,   -1,   -1,   -1,   40,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,
  258,  259,  260,  261,   -1,  263,  264,  265,  256,  257,
  258,  259,  260,  261,   -1,  263,  264,  265,  256,  257,
  258,  259,  260,  261,   -1,  263,  264,  265,  256,  257,
  258,  259,  260,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,  261,  261,  256,  257,  258,  259,  260,   -1,   -1,
  263,  264,  265,  256,  257,  258,  259,  260,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 265
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"CHAR","DOT","CCL","NCCL",
"OR","CAT","STAR","PLUS","QUEST",
};
static const char *yyrule[] = {
"$accept : s",
"s : t",
"t : b r",
"t : OR b r OR",
"t : OR b r",
"t : b r OR",
"b :",
"r : CHAR",
"r : DOT",
"r : CCL",
"r : NCCL",
"r : r OR r",
"r : r r",
"r : r STAR",
"r : r PLUS",
"r : r QUEST",
"r : '(' r ')'",
"r : error",

};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static unsigned yystacksize;
#line 149 "egrep.y"
static int
yyerror(char *s)
{
	message = s;
	longjmp(env, 1);
	return 1;		/* silence a warning */
}

static int
yylex(void)
{
    int cclcnt, x;
    char c, d;

    switch(c = nextch()) {
    case '|':
	return (OR);
    case '*':
	return (STAR);
    case '+':
	return (PLUS);
    case '?':
	return (QUEST);
    case '(':
	return (c);
    case ')':
	return (c);
    case '.':
	return (DOT);
    case '\0':
	return (0);
    case '\n':
	return (OR);
    case '[': 
	x = CCL;
	cclcnt = 0;
	count = nxtchar++;
	if ((c = nextch()) == '^') {
	    x = NCCL;
	    c = nextch();
	}
	do {
	    if (c == '\0')
		synerror();
	    if (c == '-'
		&& cclcnt > 0
		&& chars[nxtchar-1] != 0) {
		if ((d = nextch()) != 0) {
		    c = chars[nxtchar-1];
		    while ((unsigned int)c < (unsigned int)d) {
			if (nxtchar >= MAXLIN)
			    overflo();
			chars[nxtchar++] = ++c;
			cclcnt++;
		    }
		    continue;
		} /* if() */
	    } /* if() */
	    if (nxtchar >= MAXLIN)
		overflo();
	    chars[nxtchar++] = c;
	    cclcnt++;
	} while ((c = nextch()) != ']');
	chars[count] = cclcnt;
	return (x);
    case '\\':
	if ((c = nextch()) == '\0')
	    synerror();
	/* not reached */
    case '$':
    case '^':
	c = '\n';
	/* fall through */
    default:
	yylval = c;
	return (CHAR);
    }
}

static void
synerror(void)
{
    yyerror("Syntax error");
}

static unsigned int
enter(int x)
{
    if(line >= MAXLIN)
	overflo();
    name[line] = x;
    left[line] = 0;
    right[line] = 0;
    return(line++);
}

static unsigned int
cclenter(int x)
{
    unsigned int linno;

    linno = enter(x);
    right[linno] = count;
    return (linno);
}

static int
node(int x, int l, int r)
{
    if(line >= MAXLIN)
	overflo();
    name[line] = x;
    left[line] = l;
    right[line] = r;
    parent[l] = line;
    parent[r] = line;
    return(line++);
}

static int
unary(int x, int d)
{
    if(line >= MAXLIN)
	overflo();
    name[line] = x;
    left[line] = d;
    right[line] = 0;
    parent[d] = line;
    return(line++);
}

static void
overflo(void)
{
    yyerror("internal table overflow");
}

static void
cfoll(int v)
{
    unsigned int i;

    if (left[v] == 0) {
	count = 0;
	for (i = 1; i <= line; i++) 
	    tmpstat[i] = 0;
	follow(v);
	add(foll, v);
    } else if (right[v] == 0)
	cfoll(left[v]); 
    else {
	cfoll(left[v]);
	cfoll(right[v]);
    }
}

static void
cgotofn(void)
{
    unsigned int i, n, s;
    int c, k;
    char symbol[NCHARS];
    unsigned int j, l, pc, pos;
    unsigned int nc;
    int curpos;
    unsigned int num, number, newpos;

    count = 0;
    for (n=3; n<=line; n++)
	tmpstat[n] = 0;
    if (cstate(line-1)==0) {
	tmpstat[line] = 1;
	count++;
	out[0] = 1;
    }
    for (n=3; n<=line; n++)
	initstat[n] = tmpstat[n];
    count--;		/*leave out position 1 */
    icount = count;
    tmpstat[1] = 0;
    add(state, 0);
    n = 0;
    for (s = 0; s <= n; s++)  {
	if (out[s] == 1)
	    continue;
	for (i = 0; i < NCHARS; i++)
	    symbol[i] = 0;
	num = positions[state[s]];
	count = icount;
	for (i = 3; i <= line; i++)
	    tmpstat[i] = initstat[i];
	pos = state[s] + 1;
	for (i = 0; i < num; i++) {
	    curpos = positions[pos];
	    if ((c = name[curpos]) >= 0) {
		if (c < NCHARS) {
		    symbol[c] = 1;
		} else if (c == DOT) {
		    for (k = 0; k < NCHARS; k++)
			if (k != '\n')
			    symbol[k] = 1;
		} else if (c == CCL) {
		    nc = chars[right[curpos]];
		    pc = right[curpos] + 1;
		    for (j = 0; j < nc; j++)
			symbol[(unsigned char)(chars[pc++])] = 1;
		} else if (c == NCCL) {
		    nc = chars[right[curpos]];
		    for (j = 0; j < NCHARS; j++) {
			pc = right[curpos] + 1;
			for (l = 0; l < nc; l++)
			    if (j==(unsigned char)(chars[pc++]))
				goto cont;
			if (j != '\n')
			    symbol[j] = 1;
		    cont:
			;
		    }
		}
	    }
	    pos++;
	} /* for (i) */
	for (c=0; c<NCHARS; c++) {
	    if (symbol[c] == 1) {
		/* nextstate(s,c) */
		count = icount;
		for (i=3; i <= line; i++)
		    tmpstat[i] = initstat[i];
		pos = state[s] + 1;
		for (i=0; i<num; i++) {
		    curpos = positions[pos];
		    if ((k = name[curpos]) >= 0)
			if ((k == c)
			    || (k == DOT)
			    || (k == CCL && member(c, right[curpos], 1))
			    || (k == NCCL && member(c, right[curpos], 0))
			    ) {
			    number = positions[foll[curpos]];
			    newpos = foll[curpos] + 1;
			    for (j = 0; j < number; j++) {
				if (tmpstat[positions[newpos]] != 1) {
				    tmpstat[positions[newpos]] = 1;
				    count++;
				}
				newpos++;
			    }
			}
		    pos++;
		} /* end nextstate */
		if (notin(n)) {
		    if (n >= NSTATES)
			overflo();
		    add(state, ++n);
		    if (tmpstat[line] == 1)
			out[n] = 1;
		    gotofn[s][c] = n;
		} else {
		    gotofn[s][c] = xstate;
		}
	    } /* if (symbol) */
	} /* for(c) */
    } /* for(s) */
}

static int
cstate(int v)
{
	int b;
	if (left[v] == 0) {
		if (tmpstat[v] != 1) {
			tmpstat[v] = 1;
			count++;
		}
		return(1);
	}
	else if (right[v] == 0) {
		if (cstate(left[v]) == 0) return (0);
		else if (name[v] == PLUS) return (1);
		else return (0);
	}
	else if (name[v] == CAT) {
		if (cstate(left[v]) == 0 && cstate(right[v]) == 0) return (0);
		else return (1);
	}
	else { /* name[v] == OR */
		b = cstate(right[v]);
		if (cstate(left[v]) == 0 || b == 0) return (0);
		else return (1);
	}
}

static int
member(int symb, int set, int torf)
{
    unsigned int i, num, pos;

    num = chars[set];
    pos = set + 1;
    for (i = 0; i < num; i++)
	if (symb == (unsigned char)(chars[pos++]))
	    return (torf);
    return (!torf);
}

static int
notin(int n)
{
	int i, j, pos;
	for (i=0; i<=n; i++) {
		if (positions[state[i]] == count) {
			pos = state[i] + 1;
			for (j=0; j < count; j++)
				if (tmpstat[positions[pos++]] != 1) goto nxt;
			xstate = i;
			return (0);
		}
		nxt: ;
	}
	return (1);
}

static void
add(int *array, int n)
{
    unsigned int i;

    if (nxtpos + count > MAXPOS)
	overflo();
    array[n] = nxtpos;
    positions[nxtpos++] = count;
    for (i=3; i <= line; i++) {
	if (tmpstat[i] == 1) {
	    positions[nxtpos++] = i;
	}
    }
}

static void
follow(unsigned int v)
{
    unsigned int p;

    if (v == line) 
	return;
    p = parent[v];
    switch(name[p]) {
    case STAR:
    case PLUS:	cstate(v);
	follow(p);
	return;

    case OR:
    case QUEST:	follow(p);
	return;

    case CAT:
	if (v == left[p]) {
	    if (cstate(right[p]) == 0) {
		follow(p);
		return;
	    }
	} else 
	    follow(p);
	return;
    case FINAL:
	if (tmpstat[line] != 1) {
	    tmpstat[line] = 1;
	    count++;
	}
	return;
    }
}

char *
egrepinit(char *egreppat)
{
    /* initialize the global data */
    memset(gotofn, 0, sizeof(gotofn));
    memset(state, 0, sizeof(state));
    memset(out, 0, sizeof(out));
    line = 1;
    memset(name, 0, sizeof(name));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(parent, 0, sizeof(parent));
    memset(foll, 0, sizeof(foll));
    memset(positions, 0, sizeof(positions));
    memset(chars, 0, sizeof(chars));
    nxtpos = 0;
    nxtchar = 0;
    memset(tmpstat, 0, sizeof(tmpstat));
    memset(initstat, 0, sizeof(initstat));
    xstate = 0;
    count = 0;
    icount = 0;
    input = egreppat;
    message = NULL;
    if (setjmp(env) == 0) {
	yyparse();
	cfoll(line-1);
	cgotofn();
    }
    return(message);
}

int
egrep(char *file, FILE *output, char *format)
{
    char *p;
    unsigned int cstat;
    int ccount;
    char buf[2*BUFSIZ];
    char *nlp;
    unsigned int istat;
    int in_line;
    FILE *fptr;

    if ((fptr = myfopen(file, "r")) == NULL) 
	return(-1);

    ccount = 0;
    lnum = 1;
    in_line = 0;
    p = buf;
    nlp = p;
    if ((ccount = fread(p, sizeof(char), BUFSIZ, fptr)) <= 0)
	goto done;
    in_line = 1;
    istat = cstat = (unsigned int) gotofn[0]['\n'];
    if (out[cstat])
	goto found;
    for (;;) {
	if (!iflag)
	    cstat = (unsigned int) gotofn[cstat][(unsigned int)*p&0377];
	/* all input chars made positive */
	else
	    cstat = (unsigned int) gotofn[cstat][tolower((int)*p&0377)];
	/* for -i option*/
	if (out[cstat]) {
	found:
	    for(;;) {
		if (*p++ == '\n') {
		    in_line = 0;
		succeed:
		    fprintf(output, format, file, lnum);
		    if (p <= nlp) {
			while (nlp < &buf[2*BUFSIZ])
			    putc(*nlp++, output);
			nlp = buf;
		    }
		    while (nlp < p)
			putc(*nlp++, output);
		    lnum++;
		    nlp = p;
		    if ((out[(cstat=istat)]) == 0)
			goto brk2;
		} /* if (p++ == \n) */
	    cfound:
		if (--ccount <= 0) {
		    if (p <= &buf[BUFSIZ]) {
			ccount = fread(p, sizeof(char), BUFSIZ, fptr);
		    } else if (p == &buf[2*BUFSIZ]) {
			p = buf;
			ccount = fread(p, sizeof(char), BUFSIZ, fptr);
		    } else {
			ccount = fread(p, sizeof(char), &buf[2*BUFSIZ] - p,
				       fptr);
		    }
		    if (ccount <= 0) {
			if (in_line) {
			    in_line = 0;
			    goto succeed;
			}
			goto done;
		    }
		} /* if(ccount <= 0) */
		in_line = 1;
	    } /* for(ever) */
	} /* if(out[cstat]) */

	if (*p++ == '\n') {
	    in_line = 0;
	    lnum++;
	    nlp = p;
	    if (out[(cstat=istat)])
		goto cfound;
	}
    brk2:
	if (--ccount <= 0) {
	    if (p <= &buf[BUFSIZ]) {
		ccount = fread(p, sizeof(char), BUFSIZ, fptr);
	    } else if (p == &buf[2*BUFSIZ]) {
		p = buf;
		ccount = fread(p, sizeof(char), BUFSIZ, fptr);
	    } else {
		ccount = fread(p, sizeof(char), &buf[2*BUFSIZ] - p, fptr);
	    }
	    if (ccount <= 0) 
		break;
	}
	in_line = 1;
    }
done:
    fclose(fptr);
    return(0);
}

/* FIXME HBB: should export this to a separate file and use
 * AC_REPLACE_FUNCS() */
#if !STDC_HEADERS && !defined(HAVE_MEMSET) && !defined(HAVE_MEMORY_H)
/*LINTLIBRARY*/
/*
 * Set an array of n chars starting at sp to the character c.
 * Return sp.
 */
char *
memset(char *sp, char c, int n)
{
	char *sp0 = sp;

	while (--n >= 0)
		*sp++ = c;
	return (sp0);
}
#endif

void
egrepcaseless(int i)
{
	iflag = i;	/* simulate "egrep -i" */
}
#line 835 "egrep.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    yystate = 0;
    *yyssp = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yyssp = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yyssp = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 106 "egrep.y"
	{ unary(FINAL, yyvsp[0]);
		  line--;
		}
break;
case 2:
#line 111 "egrep.y"
	{ yyval = node(CAT, yyvsp[-1], yyvsp[0]); }
break;
case 3:
#line 113 "egrep.y"
	{ yyval = node(CAT, yyvsp[-2], yyvsp[-1]); }
break;
case 4:
#line 115 "egrep.y"
	{ yyval = node(CAT, yyvsp[-1], yyvsp[0]); }
break;
case 5:
#line 117 "egrep.y"
	{ yyval = node(CAT, yyvsp[-2], yyvsp[-1]); }
break;
case 6:
#line 120 "egrep.y"
	{ yyval = enter(DOT);
		   yyval = unary(STAR, yyval); }
break;
case 7:
#line 124 "egrep.y"
	{ yyval = enter(yyvsp[0]); }
break;
case 8:
#line 126 "egrep.y"
	{ yyval = enter(DOT); }
break;
case 9:
#line 128 "egrep.y"
	{ yyval = cclenter(CCL); }
break;
case 10:
#line 130 "egrep.y"
	{ yyval = cclenter(NCCL); }
break;
case 11:
#line 134 "egrep.y"
	{ yyval = node(OR, yyvsp[-2], yyvsp[0]); }
break;
case 12:
#line 136 "egrep.y"
	{ yyval = node(CAT, yyvsp[-1], yyvsp[0]); }
break;
case 13:
#line 138 "egrep.y"
	{ yyval = unary(STAR, yyvsp[-1]); }
break;
case 14:
#line 140 "egrep.y"
	{ yyval = unary(PLUS, yyvsp[-1]); }
break;
case 15:
#line 142 "egrep.y"
	{ yyval = unary(QUEST, yyvsp[-1]); }
break;
case 16:
#line 144 "egrep.y"
	{ yyval = yyvsp[-1]; }
break;
#line 1087 "egrep.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = (short) yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
