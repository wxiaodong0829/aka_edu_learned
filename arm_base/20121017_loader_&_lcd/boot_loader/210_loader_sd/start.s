.globl _start
_start:
	@set sp in IRAM   @注释
	ldr sp,=0xD0037000

	@1.close WDT
	ldr r0,=0XE2700000
	mov r1,#0
	str r1,[r0]

	@2.close FIQ,IRQ
	mrs r0,CPSR
	bic r0,r0,#0XC0
	msr CPSR,r0
/*
	@4.init UART
@bl uart0_init
	@6.init NAND
	@bl nand_init	
*/	
	@3.init CLOCK
	bl clock_init


	@4.init MEMORY
	bl mem_ctrl_asm_init
	
	@set sp in DRAM
	ldr sp,=0x38000000

	@copy bootloader from nand to dram 0x20000010
	bl copy_myself
/*
	ldr r0, =0xD0020000
	ldr r1, =0x20000000	@ copy to SDRAM
	ldr r2, =0x2000		@ size = 8K

move_loop:
	ldr r3, [r0],#4
	str r3, [r1],#4
	subs r2, r2, #4
	bne move_loop

	@b mymain 
	@ here we use ldr instead of b to jump to SDRAM 
	@ in addition, we should change -T0x20000010 for using SDRAM

*/
	@ ldr 绝对跳转    (b  bl) 相对跳转
	ldr pc, =c_entry @绝对地址给 pc 如何产生绝对执行
	

							



	
