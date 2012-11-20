#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int num[], int len)
{
	int i;
	srand(time(NULL));
	for(i = 0; i < len; i++)
	num[i] = rand()% 100;
}
void show(int num[], int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%d", num[i]);
	}
	printf("\n");
}
void bubble_sort(int num[], int len)
{
	int i, j, tmp;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - i - 1; j++)
		{
			if (num[j] > num[j + 1])
			{
				tmp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = tmp;
			}
		}
	}
}
int main(void)
{
	int num[5];
	init(num, 5);
	
	show(num, 5);
	bubble_sort(num, 5);
	show(num, 5);
	
	return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int num[], int len)
{
[0xe92d4070]   stmfd    r13!,{r4-r6,r14}
[0xe1a06001]   mov      r6,r1
[0xe1a05000]   mov      r5,r0
	int i;   
	srand(time(NULL));   
[0xe3a00000]   mov      r0,#0
[0xeb0000cd]   bl       time
[0xeb000058]   bl       srand
	for(i = 0; i < len; i++)   
[0xe3a04000]   mov      r4,#0
[0xea000005]   b        0x80e0  ; (init + 0x38)
......
[0xe2844001]   add      r4,r4,#1
[0xe1540006]   cmp      r4,r6
[0xbafffff7]   blt      0x80c8  ; (init + 0x20)
	num[i] = rand()% 100;   
[0xeb000078]   bl       rand
[0xe1a01000]   mov      r1,r0
[0xe3a00064]   mov      r0,#0x64
[0xeb000091]   bl       __rt_sdiv
[0xe7851104]   str      r1,[r5,r4,lsl #2]
}
[0xe8bd8070]   ldmfd    r13!,{r4-r6,pc}
void show(int num[], int len)
{
[0xe92d4070]   stmfd    r13!,{r4-r6,r14}
[0xe1a06001]   mov      r6,r1
[0xe1a05000]   mov      r5,r0
	int i;   
	for (i = 0; i < len; i++)   
[0xe3a04000]   mov      r4,#0
[0xea000003]   b        0x8110  ; (show + 0x24)
......
[0xe2844001]   add      r4,r4,#1
[0xe1540006]   cmp      r4,r6
[0xbafffff9]   blt      0x8100  ; (show + 0x14)
	{   
		printf("%d", num[i]);      
[0xe7951104]   ldr      r1,[r5,r4,lsl #2]
[0xe28f0018]   add      r0,pc,#0x18 ; #0x8124
[0xeb000030]   bl       _printf
	}   
	printf("\n");   
[0xe28f0008]   add      r0,pc,#8 ; #0x8128
[0xe8bd4070]   ldmfd    r13!,{r4-r6,r14}
[0xea00002a]   b        _printf
[0x00006425]   dcd      0x00006425  %d..
[0x0000000a]   dcd      0x0000000a  ....
}
void bubble_sort(int num[], int len)
{
[0xe92d4070]   stmfd    r13!,{r4-r6,r14}
	int i, j, tmp;   
	for (i = 0; i < len - 1; i++)   
[0xe3a0e000]   mov      r14,#0
[0xe2416001]   sub      r6,r1,#1
[0xea00000e]   b        0x8178  ; (bubble_sort + 0x4c)
......
[0xe28ee001]   add      r14,r14,#1
[0xe15e0006]   cmp      r14,r6
[0xbaffffee]   blt      0x813c  ; (bubble_sort + 0x10)
	{   
		for (j = 0; j < len - i - 1; j++)      
[0xe041300e]   sub      r3,r1,r14
[0xe2435001]   sub      r5,r3,#1
[0xe3a02000]   mov      r2,#0
[0xea000007]   b        0x816c  ; (bubble_sort + 0x40)
......
[0xe2822001]   add      r2,r2,#1
[0xe1550002]   cmp      r5,r2
[0xcafffff5]   bgt      0x814c  ; (bubble_sort + 0x20)
		{      
			if (num[j] > num[j + 1])         
[0xe7903102]   ldr      r3,[r0,r2,lsl #2]
[0xe0804102]   add      r4,r0,r2,lsl #2
[0xe594c004]   ldr      r12,[r4,#4]
[0xe153000c]   cmp      r3,r12
[0xda000001]   ble      0x8168  ; (bubble_sort + 0x3c)
			{         
				tmp = num[j];            
				num[j] = num[j + 1];            
[0xe780c102]   str      r12,[r0,r2,lsl #2]
				num[j + 1] = tmp;            
[0xe5843004]   str      r3,[r4,#4]
			}         
		}      
	}   
}
[0xe8bd8070]   ldmfd    r13!,{r4-r6,pc}
int main(void)
{
[0xe52de004] * str      r14,[r13,#-4]!
[0xe24dd014]   sub      r13,r13,#0x14
	int num[5];   
	init(num, 5);   
[0xe3a01005]   mov      r1,#5
[0xe1a0000d]   mov      r0,r13
[0xebffffc3]   bl       init
	   
	show(num, 5);   
[0xe3a01005]   mov      r1,#5
[0xe1a0000d]   mov      r0,r13
[0xebffffd1]   bl       show
	bubble_sort(num, 5);   
[0xe3a01005]   mov      r1,#5
[0xe1a0000d]   mov      r0,r13
[0xebffffde]   bl       bubble_sort
	show(num, 5);   
[0xe3a01005]   mov      r1,#5
[0xe1a0000d]   mov      r0,r13
[0xebffffcb]   bl       show
	   
	return 0;   
[0xe3a00000]   mov      r0,#0
[0xe28dd014]   add      r13,r13,#0x14
}
[0xe49df004]   ldr      pc,[r13],#4



*/