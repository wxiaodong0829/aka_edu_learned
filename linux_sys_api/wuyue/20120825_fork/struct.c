/*对齐：
 *
 * 按谁对齐：此数据的地址能对几整除
 *
 * 结构体内部对齐：1，K字节大小的数据，按K个字节对齐  2，编译器 指定对齐的字节数  3，要考虑结构体数组情况
 *				结构体内部的数据实际对齐字节：min(1, 2);		//假设内部从 0 地址开始放
 *
 * 结构体本身的对齐：1，结构体中的数据中最长的对齐数   2，编译器指定对齐字节数		3,函数中其它参数以及栈帧以上ebp,函数返回值这些固定四字节对齐的空间
 *				结构体本身的实际对齐字节：min(1, 2);
 *
 *			综合 1，2，3：若结构体大小不够4字节整除时，要向下(因为是栈帧，上面放的是ebp等)填充
 *
 *
 *
 *
 *
 * */


#include <stdio.h>
#if 0
#pragma pack(1) /*关闭对齐，用于内存不富裕的情况，对齐本质：拿空间换时间*/
#endif
#pragma pack(2) /*指定编译器对齐字节数*/
struct t1
{
    int i;
    char c1;
    short s;
    char c2;
};
#pragma pack()
struct t2
{
    int i;
    char c1;
    short s;
    char c2;
};

int main(void)
{
    short i;//int i;
    struct t1 v;
    struct t2 v2;
    //short s;

    printf("size : %d\n", sizeof(struct t1));
    printf("size : %d\n", sizeof(struct t2));
    
    printf("v : %p\n", &v);
    printf("i : %p\n", &i);
    //printf("s : %p\n", &s);
    printf("v2 : %p\n", &v2);

    return 0;
}
