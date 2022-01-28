/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 4

/* --- variable a  (character) --- */
	.type a, %object
	.size a, 1
a:
	.byte 65

/* ========================= */
/*       TEXT section        */
/* ========================= */
	.section .text
	.global main
	.type main,%function
.char:
	.word a
main:
	mov r0, #0x3
	ldr r1, .char
	swi 0x123456
	mov r3, r0
	nop
	.end
