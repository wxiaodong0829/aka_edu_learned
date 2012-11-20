	AREA Example,CODE,READONLY ;声明代码段Example

	CODE32 ;声明32位ARM指令
	ENTRY ;标识程序入口
	
START
	
	MOV R1, #3
	MOV R2, #5
	
	ADD R0, R1, R2 ; R0 = R1 + R2
	ADD R0, R1, #2 ; R0 = R1 + 2
	ADD R0, R2, R1,LSL#1 ; R0 = R2 + (R1 << 1)
	
	MOV R1, #0xf1000000
	MOV R2, #0x80000000
	
	ADD R0, R1, R2 ; R0 = R1 + R2 查看CPSR寄存器中的C位是否变化
	ADDS R3, R1, R2 ; 查看CPSR寄存器中的C位是否变化
	ADD R5, R1, R2 ; 指令中没加S，相加结果不改变CPSR中相关标志位
	
	ADC R6, R1, R2 ; 带进位加法，R6=R1+R2+（CPSR中C标志位的值）
	ADDS R5, R1, R2 ; 指令中加S，相加结果改变CPSR中相关标志位
	ADC R6, R1, R2 ; 带进位加法，R6=R1+R2+（CPSR中C标志位的值）
	MOV R4, #0x5fffffff
	MOV R5, #0x6e
	MOV R6, #0x6fffffff
	MOV R7, #0x9
	MOV R8, #0xcfffffff
	MOV R9, #0x1
	MOV R10, #0xbfffffff
	MOV R11, #0x9
	ADDS R0, R4, R8 ; 加低端的字
	ADCS R1, R5, R9 ; 加下一个字，带进位
	ADCS R2, R6, R10 ; 加第三个字，带进位
	ADCS R3, R7, R11 ; 加高端的字，带进位
	SUB R0, R2, R1 ; R0 = R2 – R1
	SUB R0, R1, #2 ; R0 = R1 - 2
	SUB R0, R2, R3,LSL#1 ; R0 = R2 - (R3 << 1)
	RSB R0, R1, R2 ; R0 = R2 - R1
	RSB R0, R1, #256 ; R0 = 256 - R1
	RSB R0, R1, R3,LSL#1 ; R0 = (R3 << 1) – R1
	MOV R1, #3
	MOV R2, #5
	MUL R3, R1, R2
	B START
	
	
	
	END