	AREA aaa,CODE,READONLY
	CODE32
	ENTRY
AAA
	MOV R0,#1
	MOV R1,#2
	ADD R2,R1,R2;
	MOV R3,#0X8000
	STR R2,[R3];给0x8000处写入 R2 的值 0x02
	BL  AAA
	MOV R6,#1
	B .
	
	END
	