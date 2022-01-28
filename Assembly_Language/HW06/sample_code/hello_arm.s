/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 4

/* --- a string "Hello ARM" --- */
a:
	.ascii "Hello ARM\n"

/* ========================= */
/*       TEXT section        */
/* ========================= */
	.section .text
	.global main
	.type main,%function
.string:
	.word a
main:
	mov r3, #9
	mov r0, #0x3
	ldr r1, .string
loop:
	cmp r3, #0
	swigt 0x123456
	addgt r1, r1, #1
	subgt r3, r3, #1
	bgt loop

