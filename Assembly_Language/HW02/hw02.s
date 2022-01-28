/* ========================= */
/* TEXT section */
/* ========================= */
    .section .text
    .global main
    .type main,%function
main:
    ldr r1, =#10  // r1 = 10
    ldr r2, =#20  // r2 = 20 
    ldr r3, =#12  // r1 = 30 

    eor r0, r0, r0          // r0 = 0
    add r0, r0, r1, LSL #1  // r0 += 2 * r1
    add r0, r0, r2, LSL #2  // r0 += 4 * r2
    add r0, r0, r3, LSL #3  // r0 += 8 * r3

    nop     // mov r0, r0
    .end
