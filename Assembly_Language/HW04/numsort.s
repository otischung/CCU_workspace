    .section .text
    .global NumSort
    .type NumSort, %function
NumSort:
    // function start
    stmfd   sp!, {r0-r9, fp, ip, lr}

    // begin your function
    // Get array size from r9
    // Get array address from r10

    // Do NumSort
    /*---- Copy Array ----*/
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    ldr r2, [r1], #4
    str r2, [r10], #4
    sub r10, r10, #32

    sub r0, r9, #1      // i = arrsize - 1
LOOP1:
    eor r1, r1, r1      // j = 0
LOOP2:
    ldr r2, [r10, r1]   // arr[j]
    add r1, r1, #4
    ldr r3, [r10, r1]   // arr[j + 1]
    cmp r2, r3          // if (arr[j] > arr[j + 1])
    movgt r4, r2        // swap arr[j] and arr[j + 1]
    movgt r2, r3
    movgt r3, r4
    cmp r0, r1          // if (j < i)
    bgt LOOP2
    cmp r0, #0          // if (i > 0)
    subgt r0, r0, #1    // --i
    bgt LOOP1

    // Put result array's address into r10
    // end of your function
    // function exit
    ldmfd sp, {r0-r9, fp, ip, pc}  // Slides is wrong here.
    .end
