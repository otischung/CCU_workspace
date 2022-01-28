/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 4

/* --- variable a --- */
	.type a, %object
	.size a, 8
a:
	.word 1
	.word 2

/* --- variable b --- */
	.type b, %object
	.size b, 4
b:
	.word 3

c:
	.space 8, 0

/* ========================= */
/*       TEXT section        */
/* ========================= */
	.section .text
	.global main
	.type main,%function
.matrix:
	.word a
	.word b
	.word c
main:
	ldr r0, .matrix
	ldr r1, [r0], #4  /* r1 := mem32[r0] */
			  /* r0 := r0 + 4    */
	ldr r2, [r0]

	ldr r0, .matrix + 4
	ldr r3, [r0]      /* r3 := mem32[r0] */

	ldr r4, .matrix + 8

	mul r5, r3, r1
	mul r6, r3, r2

	str r5, [r4], #4  /* mem32[r4] := r5 */
                          /* r4 := r4 + 4    */
	str r6, [r4]
	nop
	.end
