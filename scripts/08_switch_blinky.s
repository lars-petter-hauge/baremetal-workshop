.global _start

.equ LEDR_BASE, 0xFF200000
.equ SW_BASE, 0xFF200040

_start:
    ldr     r0, =LEDR_BASE
	ldr		r4, =SW_BASE

blink_loop:
	ldr		r5, [r4]
	ldr		r3, [r0]
	orr		r3, r3, r5
    str     r3, [r0]
    bl      delay

	ldr		r3, =0
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
