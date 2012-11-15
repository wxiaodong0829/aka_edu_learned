#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define B (((0      //“（” 的个数是有几个bit位
#define _ )*2
#define X )*2+1

#define E    B  _ _ _		//依次代表 东     南   西    北   000 001 010 011 
#define S    B  _ _ X
#define W    B  _ X _
#define N    B  _ X X
							//依次代表 东北  西北 西南 东南  100 101 110 111 
#define AA   B  X _ _
#define BB   B  X _ X
#define CC   B  X X _
#define DD   B  X X X

#define M    B  X X X		//掩码
void bit(int x)
{
    int i;
    printf("%+11d\t", x);
    for (i=0; i<sizeof(int)*8; i++, x=x<<1)
        printf("%d%s", !!(x&0x80000000), i%4==3?" ":"");
    printf("\n");
}

/*
 *name:		print_view
 *
 *function: print the view of code of step move
 *
 *parameter: int max_step   : the people move max step
 * 
 *in: int max_step
 *
 *out: void
 *
 */
void print_view(int max_step)
{
    int b, x=0, y=0, n=0; 
//	int xy = 0, yx = 0;					//ｘｙ东北方为正方向　　　　ｙｘ　东南方为正方向
    printf(".PS 6 7\n");
    srand(time(NULL));
    do {
        switch (rand()&M) {
            case E: x++; break;
            case W: x--; break;
            case N: y++; break;
            case S: y--; break;

            case AA: x++; y++; break;
            case BB: y++; x--; break;
			case CC: x--; y--; break;
			case DD: y--; x++; break;
        }
//		printf("rand()&M = %d\t", rand()&M);
        printf("arrow to %d, %d \"%d\"\n", x, y, n);
    } while ((x || y ) && n++ < max_step);
	
    printf(".PE\n");

}

int vert(x, p, n)
{
	return x =  x ^ ((~((~0) << n)) << p);
}

int main()
{
	int x = 7;

	bit(x);
	bit(vert(x, 1, 3));

    return 0;
}
