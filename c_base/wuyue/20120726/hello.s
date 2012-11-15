#PURPOSE: Simple program that exits and returns a
#	status code back to the Linux kernel
#
#INPUT:	none
#
#OUTPUT: returns a status code. This can be viewed

.section .data

.section .text
.globl _start
_start:
	movl $1, %eax #this is the linux keernel command
	
	movl $4, %ebx
	int $0x80
