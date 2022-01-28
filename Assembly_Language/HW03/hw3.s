/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 4

/* --- variable a --- */
	.type a, %object
	.size a, 32
a:
	.word 1
	.word 2
	.word 3
	.word 4
	.word 5
	.word 6
	.word 7
	.word 8

/* --- variable b --- */
	.type b, %object
	.size b, 32
b:
	.word 8
	.word 7
	.word 6
	.word 5
	.word 4
	.word 3
	.word 2
	.word 1

/* --- variable c --- */
	.type c, %object
c:
	.space 16, 0

/* --- c should be ---*/
/*      40    30      */
/*     120    94      */

/* ========================= */
/*       TEXT section        */
/* ========================= */
	.section .text
	.global main
	.type main, %function
.matrix:  // linker will substitute them into appropriate address
	.word a
	.word b
	.word c
main:
	ldr r0, .matrix			// r0 = a
	ldr r1, .matrix + 4		// r1 = b
	ldr r2, [r0], #4		// r2 = a[0][0]
	ldr r3, [r1], #8		// r3 = b[0][0]
	mul r4, r2, r3
	eor r5, r5
	add r5, r5, r4
	ldr r2, [r0], #4		// r2 = a[0][1]
	ldr r3, [r1], #8		// r3 = b[1][0]
	mul r4, r2, r3
	add r5, r5, r4
	ldr r2, [r0], #4		// r2 = a[0][2]
	ldr r3, [r1], #8		// r3 = b[2][0]
	mul r4, r2, r3
	add r5, r5, r4
	ldr r2, [r0]			// r2 = a[0][3]
	ldr r3, [r1]			// r3 = b[3][0]
	mul r4, r2, r3
	add r5, r5, r4			// r5 = c[0][0]

	ldr r0, .matrix			// r0 = a
	ldr r1, .matrix + 4		// r1 = b
	add r1, r1, #4
	ldr r2, [r0], #4		// r2 = a[0][0]
	ldr r3, [r1], #8		// r3 = b[0][1]
	mul r4, r2, r3
	eor r6, r6
	add r6, r6, r4
	ldr r2, [r0], #4		// r2 = a[0][1]
	ldr r3, [r1], #8		// r3 = b[1][1]
	mul r4, r2, r3
	add r6, r6, r4
	ldr r2, [r0], #4		// r2 = a[0][2]
	ldr r3, [r1], #8		// r3 = b[2][1]
	mul r4, r2, r3
	add r6, r6, r4
	ldr r2, [r0]			// r2 = a[0][3]
	ldr r3, [r1]			// r3 = b[3][1]
	mul r4, r2, r3
	add r6, r6, r4			// r6 = c[0][1]

	ldr r0, .matrix			// r0 = a
	ldr r1, .matrix + 4		// r1 = b
	add r0, r0, #16
	ldr r2, [r0], #4		// r2 = a[1][0]
	ldr r3, [r1], #8		// r3 = b[0][0]
	mul r4, r2, r3
	eor r7, r7
	add r7, r7, r4
	ldr r2, [r0], #4		// r2 = a[1][1]
	ldr r3, [r1], #8		// r3 = b[1][0]
	mul r4, r2, r3
	add r7, r7, r4
	ldr r2, [r0], #4		// r2 = a[1][2]
	ldr r3, [r1], #8		// r3 = b[2][0]
	mul r4, r2, r3
	add r7, r7, r4
	ldr r2, [r0]			// r2 = a[1][3]
	ldr r3, [r1]			// r3 = b[3][0]
	mul r4, r2, r3
	add r7, r7, r4			// r7 = c[1][0]

	ldr r0, .matrix			// r0 = a
	ldr r1, .matrix + 4		// r1 = b
	add r0, r0, #16
	add r1, r1, #4
	ldr r2, [r0], #4		// r2 = a[1][0]
	ldr r3, [r1], #8		// r3 = b[0][1]
	mul r4, r2, r3
	eor r8, r8
	add r8, r8, r4
	ldr r2, [r0], #4		// r2 = a[1][1]
	ldr r3, [r1], #8		// r3 = b[1][1]
	mul r4, r2, r3
	add r8, r8, r4
	ldr r2, [r0], #4		// r2 = a[1][2]
	ldr r3, [r1], #8		// r3 = b[2][1]
	mul r4, r2, r3
	add r8, r8, r4
	ldr r2, [r0]			// r2 = a[1][3]
	ldr r3, [r1]			// r3 = b[3][1]
	mul r4, r2, r3
	add r8, r8, r4			// r8 = c[1][1]

	ldr r1, .matrix + 8
	str r5, [r1], #4
	str r6, [r1], #4
	str r7, [r1], #4
	str r8, [r1]
	ldr r1, .matrix + 8

    nop
	.end
