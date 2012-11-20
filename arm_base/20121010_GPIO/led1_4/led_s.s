	AREA LED_S,CODE,READONLY
	CODE32
	ENTRY
	

	LDR R0,=0XE0200280		;GPJCON    _0 _1 _2 _3  LED1-4 OUT
	LDR R1,=0X1111
	STR R1,[R0]
	



	LDR R2,=0XE0200284		;GPJDAT  ->  R2
START1
	MOV R3,#0XF
	MOV R4,#0X1

LOOP_1
	
	EOR R5,R3,R4
	STR R5,[R2]
	MOV R4,R4,LSL #1
	
	BL DELAY
	
	STR R3,[R2]
	
	BL DELAY
	
	CMP R4,#0X10
	BEQ START1
	B LOOP_1
	

	
	
START	
	MOV R3,#0XE			; LED1
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0XF
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0XD			; LED2
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0XF
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0XB			; LED3
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0XF
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0X7			; LED4
	STR R3,[R2]
	
	BL DELAY
	
	MOV R3,#0XF
	STR R3,[R2]
	
	BL DELAY
	
	B START
	
DELAY						; delay 
	LDR R0,=0XFFFFF
LOOP
	SUBS R0,R0,#1
	BNE LOOP
	MOV PC,LR
	
	END