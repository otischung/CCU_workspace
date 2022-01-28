/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 2
format:
	.ascii "number is %d\n\000"

/* ========================= */
/*       TEXT section        */
/* ========================= */
	.section .text
	.global main
	.type main,%function
address_format:
	.word format
main:
	mov ip, sp
	stmfd sp!, {fp, ip, lr, pc}
	sub fp, ip, #4

	ldr r0, address_format
	mov r1, #100
	bl  printf

	ldr r0, address_format
	mov r1, #123
	bl printf

	ldmea fp, {fp, sp, pc}
