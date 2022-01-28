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

/* --- "input array: " ---*/
input1:
    .ascii "Input array: \000"
input2:
    .ascii "%d \000"
input3:
    .ascii "\n\000"

/* --- "output array: " ---*/
output1:
    .ascii "Output array: \000"
output2:
    .ascii "%d \000"
output3:
    .ascii "\n\000"


/* ========================= */
/*       TEXT section        */
/* ========================= */
    .section .text
    .global main
    .type main, %function

.array:  // linker will substitute them into appropriate address
	.word a

.input:
    .word input1
    .word input2
    .word input3

.output:
    .word output1
    .word output2
    .word output3


main:
    // APCS rule call printf
    // mov ip, sp
    // stmfd sp!, {fp, ip, lr, pc}
    // sub fp, ip, #4

    ldr r5, =#32        // r5 = arr size
    ldr r6, .array      // r6 = arr address

    // call printf
    ldr r0, .input
    eor r1, r1, r1
    mov r7, lr
    bl printf  // printf will change r0-r3

    // APCS rule end printf
    // sub sp, fp, #12
    // ldmia sp, {fp, sp, lr}
    // bx lr

L1:
    ldr r0, .input + 4
    ldr r1, [r6], #4
    mov r9, lr
    bl printf
    mov lr, r9
    sub r5, r5, #4
    cmp r5, #0
    bgt L1

    ldr r0, .input + 8
    eor r1, r1, r1
    bl printf

    // put array size into r0
    ldr r0, =#32
    // put array address into r1
    ldr r1, .array
    /*------------Num Sort is Here------------*/
    bl NumSort
    /*------------Num Sort is Here------------*/
    // end of your function

    ldr r5, =#32        // r5 = arr size
    mov r6, r0          // r6 = arr address

    // call printf
    ldr r0, .output
    eor r1, r1, r1
    bl printf

L2:
    ldr r0, .output + 4
    ldr r1, [r6], #4
    mov r9, lr
    bl printf
    mov lr, r9
    sub r5, r5, #4
    cmp r5, #0
    bgt L2

    ldr r0, .output + 8
    eor r1, r1, r1
    bl printf

    mov lr, r7
    .end
