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

/* --- "open file: " ---*/
filename:
    .ascii "result.txt\000"
open:
    .word filename  // the address of file name
    .word 0x4  // write mode
    .word 10  // length of the file name

/* --- "close file: " ---*/
close:
    .space 4  // file descripter

/* --- "write file: " ---*/
write:
    .space 4  // file descripter
    .space 4  // address of the string
    .space 4  // length of the string

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
    // APCS rule start main function
    mov ip, sp
    stmfd sp!, {fp, ip, lr, pc}
    sub fp, ip, #4

    // open file
    mov r0, #0x1        // open mode
    ldr r1, =open       // addr. of parameters for open
    swi 0x123456        // ARM Angel SWI

    // store fd
    mov r10, r0         // r10 = open fd
    ldr r0, =close
    str r10, [r0]
    ldr r0, =write
    str r10, [r0]

    // malloc char buf
    mov r0, #4096
    bl malloc
    mov r9, r0          // r9 = malloc char buf addr.

    ldr r5, =#32        // r5 = arr size
    ldr r6, .array      // r6 = arr address

    // call sprintf
    mov r0, r9
    ldr r1, .input
    eor r2, r2, r2
    bl sprintf          // sprintf will change r0-r3, r3 = addr. of \0

    b L1                // This command is not important, just for debugger to step in.
L1:
    mov r0, r3
    ldr r1, .input + 4
    ldr r2, [r6], #4
    bl sprintf
    sub r5, r5, #4
    cmp r5, #0
    bgt L1

    mov r0, r3
    ldr r1, .input + 8
    eor r2, r2, r2
    bl sprintf

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

    // call sprintf
    mov r0, r3
    ldr r1, .output
    eor r2, r2, r2
    bl sprintf

    b L2  // This command is not important, just for debugger to step in.
L2:
    mov r0, r3
    ldr r1, .output + 4
    ldr r2, [r6], #4
    bl sprintf
    sub r5, r5, #4
    cmp r5, #0
    bgt L2

    mov r0, r3
    ldr r1, .output + 8
    eor r2, r2, r2
    bl sprintf

    // output to stdout
    mov r0, r9
    mov r8, r3
    bl printf
    mov r3, r8

    // write to file
    ldr r0, =write + 4
    str r9, [r0]
    ldr r0, =write + 8
    sub r1, r3, r9
    str r1, [r0]
    mov r0, #0x5        // write mode
    ldr r1, =write      // addr. of parameters for writen
    swi 0x123456        // ARM Angel SWI

    // close the file
    mov r0, #0x2
    ldr r1, =close
    swi 0x123456 

    // APCS rule end main function
    sub sp, fp, #12
    ldmia sp, {fp, sp, lr}
    bx lr

    .end
