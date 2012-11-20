	AREA led,CODE,READONLY
	CODE32
	ENTRY
	
LED_START
	ldr r0,=0xe0200280		;GPJ2CON
	mov r1,#0x1
	str r1,[r0]
	
	ldr r0,=0xe0200284		;GPJ2DAT
	mov r1,#0
	str r1,[r0]
	
	B LED_START
	
	
	END