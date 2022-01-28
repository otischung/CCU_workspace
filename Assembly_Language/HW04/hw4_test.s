/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 4

/* --- variable a --- */
	.type a, %object
	.size a, 32
a:
	.word 12
	.word 4
	.word 2
	.word 45
	.word 23
	.word 8
	.word 50
	.word 67

/* --- variable b --- */
	.type b, %object
b:
	.space 32, 0

/* ========================= */
/*       TEXT section        */
/* ========================= */
    .section .text
    .global main
    .type main, %function

.array:  // linker will substitute them into appropriate address
	.word a
    .word b

main:
    mov     ip, sp
    stmfd   sp!, {fp, ip, lr, pc}
    sub     fp, ip, #4

    // prepare input array


    // put array size into r9
    ldr r9, =#32
    ; mov r9, #32
    // put array address into r10
    ldr r1, .array
    ldr r10, .array + 4

    bl      NumSort
    // end of your function
    nop
    ldmea   fp, {fp, sp, pc}
    .end
