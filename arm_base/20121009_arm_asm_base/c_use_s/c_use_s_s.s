	AREA C_USE_S,CODE,READONLY
	CODE32
	
	EXPORT strcopy

strcopy
	
	LDRB R2,[R1],#1
	STRB R2,[R0],#1
	
	CMP R2, #0
	BNE strcopy
	
	MOV PC, LR
	
	END