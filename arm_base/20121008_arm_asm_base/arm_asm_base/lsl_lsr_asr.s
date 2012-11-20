	AREA MOV,CODE,READONLY
	CODE32
	ENTRY
	
LOOP
	
	
	mov r1, #12;			◊Û“∆
	mov r0, r1, lsl #2
	mov r3, r1, lsl #1
	
	mov r0, #0xf;			”““∆
	mov r4, r0, lsr #1
	mov r1, #0xf0000000
	mov r4, r1, asr #1
	mov r3, r1, asr #2
	
	
	bl LOOP
	nop
	
	
	
	END