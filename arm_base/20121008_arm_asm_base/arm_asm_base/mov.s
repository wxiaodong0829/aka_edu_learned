	AREA MOV,CODE,READONLY
	CODE32
	ENTRY
	
	mov r0,#0x10
	mov r1,#0
	mov r2,r0
	mov r3,r2
	mov r5,#0xf000000f
	
	mvn r0,#0
	mvn r1,#0xffffff00
	
	
	
	
	
	END