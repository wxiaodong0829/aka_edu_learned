/*************************************************************************
    > File Name: rpn.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月19日 星期四 19时48分46秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP	100		/* max size of operand of operator */
#define NUMBER  '0'		/* signal that a number was found */

int getop(char []);

