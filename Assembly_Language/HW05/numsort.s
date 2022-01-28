    .section .text
    .global NumSort
    .type NumSort, %function
NumSort:
    // function start
    stmfd   sp!, {r1-r10, fp, ip, lr}

    // begin your function
    // Get array size from r0
    // Get array address from r1

    mov r5, r0              // r5 = arr size
    mov r6, r1              // r6 = arr addr.
    mov r7, lr              // store lr
    /*---- Malloc Array ----*/
    bl malloc               // r0 = malloc addr. r1, r2, r12, lr will change.
    mov lr, r7              // restore lr
    mov r3, r5
    mov r8, r0              // copy r0 addr.

    /*---- Copy Array ----*/
LOOP3: 
    ldr r4, [r6], #4        // r4 = *a; a += 4;
    str r4, [r0], #4        // *b = r4; b += 4;
    sub r3, r3, #4          // r3 -= 1;
    cmp r3, #0              // if (r3 > 0)
    bgt LOOP3               // goto COPY;

    mov r0, r8              // restore r0 addr.

    /*---- Bubble Sort ----*/
    sub r7, r5, #4      // i = arrsize - 1
LOOP1:
    eor r8, r8, r8      // j = 0
LOOP2:
    mov r3, r0
    add r3, r3, r8      // &arr[j] 
    ldr r9, [r3]        // arr[j]
    add r8, r8, #4
    mov r4, r0
    add r4, r4, r8      // &arr[j + 1]
    ldr r10, [r4]       // arr[j + 1]
    cmp r9, r10         // if (arr[j] > arr[j + 1])
    strgt r9, [r4]      // swap arr[j] and arr[j + 1]
    strgt r10, [r3]
    cmp r7, r8          // if (j < i)
    bgt LOOP2
    cmp r7, #0          // if (i > 0)
    subgt r7, r7, #4    // --i
    bgt LOOP1

    // end of your function
    // function exit
    ldmfd sp!, {r1-r10, fp, ip, pc}  // Slides is wrong here.
    .end
