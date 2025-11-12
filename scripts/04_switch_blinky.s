.global _start

.equ LEDR_BASE, 0xFF200000

_start:
    ldr     r0, =LEDR_BASE
    ldr     r4, =SW_BASE

blink_loop:
    ldr     r3, [r4]
    str     r3, [r0]
    bl      delay

    mov     r1, #0
    str     r1, [r0]
    bl      delay

    b       blink_loop

delay:
    ldr     r2, =10000000

waitloop:
    sub     r2, #1
    cmp     r2, #0
    bne     waitloop
    bx      lr
