/*************************************************************************
    > File Name: assert.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月30日 星期一 17时56分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void _Assert(char *mesg)
{
	fputs(mesg, stderr);
	fputs(" -- assertion failed\n", stderr);
//	abort();
}

#undef assert   

#ifdef NDEBUG
	#define assert(test) ((void)0)
#else
	void _Assert(char *);
	// macros
	#define _STR(x) _VAL(x)
	#define _VAL(x) #x
	#define assert(test) ((test) ? (void)0 \
		: _Assert(__FILE__"."_STR(__LINE__)" "#test))
#endif
