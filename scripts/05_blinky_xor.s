.global _start

.equ LEDR_BASE, 0xFF200000

_start:
    ldr     r0, =LEDR_BASE

blink_loop:
	ldr		r3, [r0]
	eor		r3, r3, #1
    str     r3, [r0]
    bl      delay

    b       blink_loop

delay:
    ldr     r2, =10000000

waitloop:
    sub     r2, #1
    cmp     r2, #0
    bne     waitloop
    bx      lr
