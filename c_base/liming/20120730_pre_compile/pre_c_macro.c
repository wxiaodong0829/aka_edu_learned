/*************************************************************************
    > File Name: pre_c_macro.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月30日 星期一 15时53分23秒
 ************************************************************************/

#include <stdio.h>

#define DEBUG
#ifdef DEBUG
	#define PRINT_STR(s) printf("<%s> [%d] %s() "#s" = %s\n", __FILE__, __LINE__, __func__, s);
	#define PRINT_INT(n) printf("<%s> [%d] %s() "#n" = %d\n", __FILE__, __LINE__, __func__, n);
#else
	#define PRINT(s)
#endif


//#define PRINT_STR(n) printf(#n " : %s\n", n);
//#define PRINT_INT(n) printf(#n " : %d\n", n);

void func_test(void)
{
	char a[] = "wxiaodong0829@163.com";
	int b = 100;
	PRINT_STR("wxiaodong0829");
	PRINT_STR(a);

	PRINT_INT(10);
	PRINT_INT(b);

}
int main(void)
{
//	PRINT_INT(__LINE__);
//	PRINT_INT(__STDC__);
//	PRINT_STR(__FILE__);
//	PRINT_STR(__TIME__);
//	PRINT_STR(__DATE__);
	char a[] = "wxiaodong0829@163.com";
	int b = 100;
	PRINT_STR("wxiaodong0829");
	PRINT_STR(a);

	PRINT_INT(10);
	PRINT_INT(b);


	func_test();
	return 0;
}
