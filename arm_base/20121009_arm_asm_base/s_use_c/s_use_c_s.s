	AREA S_USE_C,CODE,READONLY
	CODE32
	ENTRY
	
	IMPORT g;
	IMPORT glovbl;
START
	MOV R0, #1
	MOV R1, #2
	MOV R2, #3
	LDR R7, =glovbl
	LDR R3, [R7]
	BL g
	MOV R8, R0
	B START
	
	END