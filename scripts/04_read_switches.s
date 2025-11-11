.global _start

.equ LEDR_BASE, 0xFF200000
.equ SW_BASE, 0xFF200040

_start:
    ldr     r0, =LEDR_BASE
    ldr     r4, =SW_BASE

switch_loop:
    ldr     r3, [r4]
    str     r3, [r0]

    b       switch_loop
