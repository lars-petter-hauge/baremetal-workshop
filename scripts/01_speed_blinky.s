.global _start

.equ LEDR_BASE, 0xFF200000

_start:
    ldr     r0, =LEDR_BASE

blink_loop:
    mov     r1, #1
    str     r1, [r0]
    mov     r1, #0
    str     r1, [r0]
    b       blink_loop
