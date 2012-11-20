	AREA MY_BUBBLE,CODE,READONLY
	CODE32
	
	EXPORT bubble_sort
bubble_sort

	stmfd r13!,{r2-r12,r14}

	mov r2, #0
loop1
	mov r3, #0
	
loop2
	mov r10, #0x4
	mul r9, r3,r10
	ldr r4,[r0, r9]
	add r5, r9, #4
	ldr r6,[r0, r5]
	cmp r4, r6
												;bgt loop2
	strhi r6, [r0, r9]
	strhi r4, [r0, r5]
	;	
	add r3, r3, #1	
	sub r7, r1, r2
	sub r7, r7, #1
	cmp r7, r3
	bgt loop2
	;
	add r2, r2, #1
	sub r8, r1, #1
	cmp r8, r2
	bgt loop1
	
	ldmfd r13!,{r2-r12,r14}
	mov pc, lr
	
	END
		