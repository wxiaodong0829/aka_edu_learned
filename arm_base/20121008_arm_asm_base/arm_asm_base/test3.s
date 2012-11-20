	; 与 或 位清0 异或
	
	
	
	AREA Example,CODE,READONLY ;声明代码段Example
	ENTRY ;标识程序入口
	CODE32 ;声明32位ARM指令
START

	mov r1, #0xffffffff

	MOV R0,#0x02
	AND R0,R0,#0x01 ;R0=R0&0x01 取出最低位数据
	MOV R1,#0x0f7
	MOV R3,#0x05
	AND R2,R1,R3 ;R2=R1&R3
	MOV R0,#0x0c1
	ORR R0,R0,#0x0F ;将R0的低4位置1
	EOR R1,R1,#0x0F ;将R1的低4位取反
	EOR R2,R1,R0 ;R2 = R1 ^ R0
	BIC R1,R1,#0x0F ;将R1的低4位清0，其他位保持不变
	BIC R1,R2,R3 ;这句是什么含义呢？将r2中 r3相应的被置1的位清0之后赋给r1
	B START
	
	END