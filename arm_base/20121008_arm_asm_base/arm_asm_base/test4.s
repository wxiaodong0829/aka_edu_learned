	AREA Example,CODE,READONLY ;声明代码段Example
	ENTRY ;标识程序入口
	CODE32 ;声明32位ARM指令
START
	mov r0, #0xffffffff
	ldr r0, =0x12345678;[0xe59f005c]   ldr      r0,0x00008068 ; = #0x12345678
						; e59 ldr
						; f(pc)   rd 目标寄存器
						; 0(r0)	  rs 源寄存器
						; 05c     pc的偏移     ldr rd,[rs, #n] n 是 rs 的偏移,此处rs 是 pc 寄存器
								  而，pc 寄存器有 预取 ，翻译，执行 三级流水线

	mov r0, #0x12
	ldr r1, =0x00008068
	ldr r0, [r1]
	ldr r0, =0xffff0000
	
	
	MOV R1,#0x10000
	MOV R4,#0x20000
	MOV R2,#0xf0000004
	MOV R3,#0x1200
	MOV R0,#0x1
	STR R0,[R1] ;[R1]<-R0，寄存器间接寻址
	LDR R5,[R1] ;R0<-[R1]，寄存器间接寻址
	ADD R5,R1,#4
	MOV R5,#0x7
	LDR R0,[R1,#4] ;R0<-[R1+4]
	LDR R0, [R1, #-4] ;R0<-[R1-4]，还可以从基址上减去偏移量来寻址
	LDR R0,[R1,#4]! ;R0<-[R1+4], R1<-R1+4，R1中的值？
	LDR R0,[R1],#4 ;R0<-[R1], R1<-R1+4，观察R0中的值，R1？
	LDR R0,[R1,R2] ;R0<-[R1+R2]，可以在方括号后附加“！”控制写回R1=R1+R2
	STR R2,[R4]
	SWP R0,R1,[R4]
	SWP R0,R0,[R1]
	SWPB R0,R1,[R2] ;这一步执行了怎样的操作？r2中低8位给r0的低8位，r0的高24位清0，r1的低8位给r2指向的地址的低8位，但r2指向的地址的高24位不被清0
	SWPB R0,R0,[R1] ;将R1所指向的存储器中的字节数据与R0中的低8位数据交换
	B START
	END