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

#define rightrot(type, number, n, y) { \
	typeof(type) x = number; \
	for (int i=0; i < n; i++) \
	x = ((x>>1) | ((x&1) << (8*sizeof(type)-1))); \
	y = x; \
} \

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


int main(void)
{
	 int numb1 = 4; 
	char ch1  = 4; 
	long lon1 = 4; 

	bit(numb1);
	typeof(numb1) numb2;
//
//	typeof(numb1) x = numb1; 
//	for (int i=0; i < 5; i++) 
//	x = ((x>>1) | ((x&1) << (sizeof(numb1)-1))); 
//	numb2 = x; /
	rightrot(typeof(numb1), 4, 3, numb2);
	bit(numb2);
//	typeof(ch1) ch2 = rightrot(typeof(ch1), 4, 1);
//	typeof(lon1) lon2 = rightrot(typeof(lon1), 4, 1);

//	printf("%d\n", numb2);
//	printf("%c\n", ch2);
//	printf("%ld\n", lon2);

	return 0;
}
