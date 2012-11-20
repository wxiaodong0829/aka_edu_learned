	AREA MOV,CODE,READONLY
	CODE32
	ENTRY
	
LOOP

	mov r1, #3
	mov r2, #5
	add r0, r1, r2
	add 	r0, r1, #2
	add 	r0, r2, r1, lsl #1
	
	add 	r5, r1, r2
	adc 	r6, r1, r2
	adds  	r5, r1, r2
	adc		r6, r1, r2
	
	subs		r0, r1, r2
	sub 	r0, r1, #256
	sub 	r2, r1, r3, lsl #1
	
	rsb		r0, r1, r2
	rsb 	r0, r1, #256
	rsb		r0, r2, r3, lsl #1
	
	mul 	r1, r2, r3;		r1 = r2 * r3

	bl LOOP
	nop
	
	
	
	END