.globl _start
_start:
	ldr sp, =0x30f00000
	B c_entry
	B .
	
	
