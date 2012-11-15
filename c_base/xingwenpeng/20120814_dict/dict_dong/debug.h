/*************************************************************************
    > File Name: debug.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时36分50秒
 ************************************************************************/
#if DEBUG == 1
#define PRINT(x)        printf("<%s> [%d] %s() "#x " = %d\n",__FILE__, __LINE__, __func__,  x)
#elif DEBUG > 1
#define PRINT(x)        printf(#x " = %d\n", x)
#else
#define PRINT(x)        
#endif



